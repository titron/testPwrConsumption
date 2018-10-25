1. Lin test method
1.1 hardware
    Connect the cable by DB9 line:
    LIN0 DB9-7(RLIN21) to LIN2 DB9-5(RLIN30)  
    LIN1 DB9-7(RLIN22) to LIN2 DB9-9(RLIN31)  
    LIN2 DB9-1(RLIN27) to LIN2 DB9-8(RLIN32)  
    LIN2 DB9-2(RLIN28) to LIN2 DB9-7(RLIN33) 
    LIN2 DB9-4(RLIN29) to LIN2 DB9-6(RLIN34) 
1.2 software
    There are 2 test patterns: 2 channels communication, 10 channels communication.
	Switch them by MACRO "ACTIVATE_LIN_BUS_NUM" in file - testlin.h
1.3 test process
    1.3.1
    2 break point are broken to toogle the timing of transciver standby ON/OFF.
	Its position are in routine "powertest_lin_rlin2_m_rlin3_s()" of testlin.c
	1.3.2
	When break, record the current.

2. File structure of source code
2.1 src/macro/... --- 接口及驱动

   [all]
   xxx_a.c/xxx_a.h --- interface that will be called by application layer(test_app), _a: application abbr
   xxx_p.c/xxx_p.h --- low driver, _p: ? abbr
   xxx_s.h         --- default setting, _s: setting
   xxx.h           --- register definition
   
   [rlin3/rlin2] // 注意：本工程里并没有调用下面autosar的接口
   xxx_as.c/xxx_as.h --- autosar interface, _as: autosar abbr
   xxx_as_cfg.h      --- autosar setting, _as_cfg: autosar configuration abbr
   
2.2 src/test_app/... --- 应用
 
    asmn_xxx_a_asmnif.c/asmn_xxx_a_asmnif.h --- // 特定环境的application,本次不适用
    
2.3 src/devices/rh850g3k-f1kh-d8/map/map_rlin2.h --- rlin2 port definition
                                                  --- rlin2 interrupt register redefinition
    src/devices/rh850g3k-f1kh-d8/map/map_rlin3.h --- rlin3 port definition
                                                  --- rlin3 interrupt register redefinition
                                                  
2.4 src/devices/rh850g3k-f1kh-d8/intvec/map_rlin2_irq.c --- rlin2 interrupt routine definition
    src/devices/rh850g3k-f1kh-d8/intvec/map_rlin3_irq.c --- rlin3 interrupt routine definition
    
2.5 CSPlus/CANFDGateway/PE1/DefaultBuild/PE1.fsy --- CS plus linker自动生成的中断函数地址信息文件
 
2.6 devices/rh850g3k-f1kh-d8/map/map_rlin2.h, map_rlin3.h --- 端口定义、寄存器基地址
 
2.7 devices/rh850g3k-f1kh-d8/intvec/map_rlin2_irq.c, map_rlin3_irq.c --- interrupt routine
   
