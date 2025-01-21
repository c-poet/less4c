#ifndef LESS4C_CORE_STYLE_H
#define LESS4C_CORE_STYLE_H

/* --------- Style Sheet单位 ----------- */
#define UNIT_CM "cm"
#define UNIT_MM "mm"
#define UNIT_IN "in"
#define UNIT_PX "px"
#define UNIT_RPX "rpx"
#define UNIT_PT "pt"
#define UNIT_PC "pc"
#define UNIT_PET "%"
#define UNIT_EM "em"
#define UNIT_REM "rem"
#define UNIT_EX "ex"
#define UNIT_CH "ch"
#define UNIT_VW "vw"
#define UNIT_VH "vh"
#define UNIT_VMIN "vmin"
#define UNIT_VMAX "vmax"

/*--------- Style Sheet 单位表 ------------ */
const char *STYLE_UNITS[16] = {
        UNIT_CM, UNIT_MM, UNIT_IN, UNIT_RPX, UNIT_PX, UNIT_PT, UNIT_PC, UNIT_PET,
        UNIT_REM, UNIT_EM, UNIT_EX, UNIT_CH, UNIT_VW, UNIT_VH, UNIT_VMIN, UNIT_VMAX
};

#endif
