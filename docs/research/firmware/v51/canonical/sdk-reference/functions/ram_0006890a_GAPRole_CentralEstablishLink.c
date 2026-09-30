/* Address: ram:0006890a; name: GAPRole_CentralEstablishLink; body bytes: 54 */

void GAPRole_CentralEstablishLink
               (undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined4 param_4)

{
  undefined1 uStack_1c;
  undefined1 uStack_1b;
  undefined1 uStack_1a;
  undefined1 uStack_19;
  undefined1 auStack_18 [20];
  
  gp = 0x20004000;
  uStack_1c = DAT_ram_20001a7c;
  uStack_1b = param_1;
  uStack_1a = param_2;
  uStack_19 = param_3;
  tmos_memcpy(auStack_18,param_4,6);
  FUN_ram_0004696a(&uStack_1c);
  return;
}

