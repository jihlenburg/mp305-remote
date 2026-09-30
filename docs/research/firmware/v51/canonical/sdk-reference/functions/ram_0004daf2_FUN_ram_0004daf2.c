/* Address: ram:0004daf2; name: FUN_ram_0004daf2; body bytes: 192 */

int FUN_ram_0004daf2(uint param_1,int param_2,undefined2 *param_3,undefined4 param_4,
                    undefined1 param_5,undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined1 *apuStack_24 [2];
  
  gp = 0x20004000;
  if (param_2 == 6) {
    apuStack_24[0] = (undefined1 *)FUN_ram_0004c344(param_3[1]);
    if (apuStack_24[0] == (undefined1 *)0x0) {
      gp = 0x20004000;
      return 2;
    }
    param_1 = (uint)*(ushort *)(apuStack_24[0] + 6);
    *param_3 = *(undefined2 *)(*(int *)(apuStack_24[0] + 0xc) + 2);
  }
  else {
    iVar3 = FUN_ram_0004c25c(param_1,param_6,param_7,apuStack_24);
    if (iVar3 != 0) {
      gp = 0x20004000;
      return iVar3;
    }
  }
  *apuStack_24[0] = param_5;
  cVar1 = DAT_ram_20001cc9;
  *(undefined2 *)(apuStack_24[0] + 2) = 5;
  cVar2 = DAT_ram_20001cc9 + '\x01';
  apuStack_24[0][4] = DAT_ram_20001cc9;
  DAT_ram_20001cc9 = cVar2;
  if (cVar1 == -1) {
    DAT_ram_20001cc9 = '\x01';
  }
  if (param_2 == 0x14) {
    param_3[1] = 5;
    *(undefined2 *)(*(int *)(apuStack_24[0] + 0xc) + 8) = param_3[4];
  }
  iVar3 = FUN_ram_0004da64(param_1,param_2,cVar1,param_3,param_4);
  if (iVar3 == 0) {
    FUN_ram_0004c5ea(apuStack_24[0],0x1e);
  }
  else {
    FUN_ram_0004c420();
  }
  return iVar3;
}

