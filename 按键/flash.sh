#!/bin/bash
# ============================================================
# MSPM0G3507 仅烧录脚本 (Standalone Flash Script)
# 使用 TI OpenOCD + CMSIS-DAP 烧录, 无需打开 IDE
#
# 用法:
#   ./flash.sh              # 烧录 Debug/car.out (默认)
#   ./flash.sh <固件路径>     # 烧录指定固件 (.out 或 .bin)
#   ./flash.sh --help       # 显示帮助
# ============================================================

set -e

# -------------------- 配置路径 --------------------
OPENOCD_BIN="/home/hua/.config/Texas Instruments/ti-embedded-debug/openocd/1.5.0.75/bin/openocd"
OPENOCD_SCRIPTS="/home/hua/.config/Texas Instruments/ti-embedded-debug/openocd/1.5.0.75/share/openocd/scripts"
INTERFACE_CFG="interface/cmsis-dap.cfg"
TARGET_CFG="target/ti_mspm0.cfg"
ADAPTER_SPEED="10000"

# 默认固件路径
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
DEFAULT_FIRMWARE="${SCRIPT_DIR}/Debug/按键.out"

# -------------------- 颜色输出 --------------------
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

log_info()  { echo -e "${CYAN}[INFO]${NC}  $*"; }
log_ok()    { echo -e "${GREEN}[OK]${NC}    $*"; }
log_warn()  { echo -e "${YELLOW}[WARN]${NC}  $*"; }
log_error() { echo -e "${RED}[ERROR]${NC} $*"; }

# -------------------- 帮助 --------------------
show_help() {
    echo "MSPM0G3507 仅烧录脚本 (Standalone Flash Script)"
    echo ""
    echo "用法:"
    echo "  $0              烧录默认固件 (Debug/car.out)"
    echo "  $0 <固件路径>     烧录指定固件 (.out 或 .bin)"
    echo "  $0 --help       显示此帮助"
    echo ""
    echo "依赖:"
    echo "  - TI OpenOCD (已内置路径)"
    echo "  - CMSIS-DAP / DAPLink 调试器"
    echo ""
    echo "示例:"
    echo "  $0                          # 烧录 Debug/car.out"
    echo "  $0 Debug/car.bin            # 烧录 bin 文件"
    echo "  $0 /path/to/other_fw.out    # 烧录其他固件"
}

# -------------------- 参数解析 --------------------
FIRMWARE="${1:-$DEFAULT_FIRMWARE}"

if [ "$1" = "--help" ] || [ "$1" = "-h" ]; then
    show_help
    exit 0
fi

# -------------------- 预检查 --------------------
echo ""
echo "============================================================"
echo "  MSPM0G3507 固件烧录工具"
echo "============================================================"
echo ""

# 检查 OpenOCD
if [ ! -f "$OPENOCD_BIN" ]; then
    log_error "找不到 OpenOCD: $OPENOCD_BIN"
    log_error "请确认 TI 嵌入式调试工具已安装"
    exit 1
fi
log_info "OpenOCD: $OPENOCD_BIN"

# 检查脚本目录
if [ ! -d "$OPENOCD_SCRIPTS" ]; then
    log_error "找不到 OpenOCD 脚本目录: $OPENOCD_SCRIPTS"
    exit 1
fi

# 检查固件文件
if [ ! -f "$FIRMWARE" ]; then
    log_error "找不到固件文件: $FIRMWARE"
    log_error "请先编译项目, 或指定正确的固件路径"
    exit 1
fi
log_info "固件: $FIRMWARE"

# 获取文件扩展名
EXT="${FIRMWARE##*.}"
FW_NAME="$(basename "$FIRMWARE")"
FW_SIZE=$(du -h "$FIRMWARE" | cut -f1)
log_info "大小: $FW_SIZE"

# -------------------- 烧录 --------------------
echo ""
log_info "开始烧录..."

if [ "$EXT" = "bin" ]; then
    # .bin 文件: 需要指定烧录地址 (MSPM0G3507 Flash 起始地址 0x00000000)
    FLASH_ADDR="0x00000000"
    log_info "格式: BIN -> Flash @ $FLASH_ADDR"

    "$OPENOCD_BIN" \
        -s "$OPENOCD_SCRIPTS" \
        -f "$INTERFACE_CFG" \
        -f "$TARGET_CFG" \
        -c "adapter speed $ADAPTER_SPEED" \
        -c "init" \
        -c "reset halt" \
        -c "flash write_image erase $FIRMWARE $FLASH_ADDR" \
        -c "verify_image $FIRMWARE $FLASH_ADDR" \
        -c "reset run" \
        -c "exit"
else
    # .out (ELF) 文件: OpenOCD 自动解析地址
    log_info "格式: ELF (自动解析地址)"

    "$OPENOCD_BIN" \
        -s "$OPENOCD_SCRIPTS" \
        -f "$INTERFACE_CFG" \
        -f "$TARGET_CFG" \
        -c "adapter speed $ADAPTER_SPEED" \
        -c "program $FIRMWARE verify reset exit"
fi

# -------------------- 结果 --------------------
if [ $? -eq 0 ]; then
    echo ""
    log_ok "烧录成功! 设备已复位运行"
    echo ""
else
    echo ""
    log_error "烧录失败! 请检查:"
    echo "  1. 调试器 (CMSIS-DAP/DAPLink) 是否正确连接"
    echo "  2. 目标板是否已上电"
    echo "  3. SWD 接线是否正确 (SWCLK, SWDIO, GND)"
    echo ""
    exit 1
fi
