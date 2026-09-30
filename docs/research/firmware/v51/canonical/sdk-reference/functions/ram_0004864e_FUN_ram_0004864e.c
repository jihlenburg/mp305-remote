/* Address: ram:0004864e; name: FUN_ram_0004864e; body bytes: 140 */

int FUN_ram_0004864e(undefined4 param_1,undefined2 *param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined2 *puVar2;
  undefined4 uStack_3c;
  undefined2 uStack_38;
  undefined2 uStack_36;
  undefined *puStack_34;
  undefined1 uStack_32;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004957c(param_1,&uStack_3c);
  if (iVar1 == 0) {
    puVar2 = param_2;
    if (param_3 != 0) {
      uStack_38 = *param_2;
      puVar2 = &uStack_38;
      uStack_36 = param_2[1];
      puStack_34 = &medeleg;
      uStack_32 = 0x28;
    }
    iVar1 = FUN_ram_000436ec(param_1,puVar2);
    if (iVar1 == 0) {
      uStack_38 = CONCAT11(uStack_38._1_1_,(char)param_3);
      tmos_memcpy(&uStack_36,param_2,0x16);
      FUN_ram_0004972e(uStack_3c,&uStack_38,9,&LAB_ram_000436ba,param_4);
    }
  }
  return iVar1;
}

