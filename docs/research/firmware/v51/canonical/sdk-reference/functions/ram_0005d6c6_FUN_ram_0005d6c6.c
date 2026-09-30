/* Address: ram:0005d6c6; name: FUN_ram_0005d6c6; body bytes: 108 */

bool FUN_ram_0005d6c6(undefined4 param_1,char *param_2)

{
  bool bVar1;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  short sStack_24;
  char cStack_22;
  char cStack_21;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  gp = 0x20004000;
  cStack_21 = param_2[3];
  cStack_22 = param_2[4];
  local_30 = 0;
  uStack_2c = 0;
  sStack_24 = (ushort)(byte)param_2[5] << 8;
  uStack_28 = 0;
  uStack_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0;
  LL_Encrypt(param_1,&local_30,&uStack_20);
  bVar1 = false;
  if ((uStack_14._3_1_ == *param_2) && (bVar1 = false, uStack_14._2_1_ == param_2[1])) {
    bVar1 = uStack_14._1_1_ == param_2[2];
  }
  return bVar1;
}

