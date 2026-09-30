/* Address: ram:0004e2a2; name: FUN_ram_0004e2a2; body bytes: 178 */

undefined4
FUN_ram_0004e2a2(undefined1 param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4,
                undefined4 param_5,undefined1 param_6,undefined2 param_7,undefined2 param_8,
                undefined2 param_9,undefined2 param_10)

{
  undefined2 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_0004df14(param_2);
  if (iVar2 == 0) {
    puVar3 = (undefined1 *)FUN_ram_0004df14(0xffff);
    uVar4 = 0x15;
    if (puVar3 != (undefined1 *)0x0) {
      puVar3[5] = param_4;
      tmos_memcpy(puVar3 + 6,param_5,6);
      *(short *)(puVar3 + 2) = (short)param_2;
      puVar3[4] = param_3;
      *(undefined2 *)(puVar3 + 0x12) = param_9;
      *puVar3 = param_1;
      *(undefined4 *)(puVar3 + 0x2c) = 0;
      *(undefined2 *)(puVar3 + 0x14) = param_10;
      puVar3[0xc] = param_6;
      *(undefined2 *)(puVar3 + 0xe) = param_7;
      *(undefined2 *)(puVar3 + 0x10) = param_8;
      uVar1 = FUN_ram_0004e244();
      *(undefined2 *)(puVar3 + 0x30) = uVar1;
      *(undefined4 *)(puVar3 + 0x34) = 0;
      *(undefined4 *)(puVar3 + 0x38) = 0;
      FUN_ram_0004de30(param_2,0);
      uVar4 = 0;
    }
  }
  else {
    uVar4 = 0x11;
  }
  return uVar4;
}

