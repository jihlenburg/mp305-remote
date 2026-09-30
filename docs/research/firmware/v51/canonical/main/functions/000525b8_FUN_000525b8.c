/* Address: 000525b8; name: FUN_000525b8; body bytes: 238 */

undefined4 * FUN_000525b8(int param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  char cVar6;
  undefined2 local_2c;
  undefined1 uStack_2a;
  undefined2 local_28;
  undefined1 uStack_26;
  
  iVar2 = FUN_000526b0();
  if (iVar2 == 0) {
    DAT_2003a5d0 = (undefined4 *)FUN_0004a360(0x39c);
  }
  puVar1 = DAT_2003a5d0;
  iVar2 = param_1;
  if (param_1 == 0) {
    iVar2 = FUN_00040890();
  }
  iVar3 = FUN_0004089c();
  iVar4 = FUN_000408b0(iVar2);
  if (iVar4 < 0x141) {
    cVar6 = '\x03';
  }
  else if (iVar4 < 0x2d0) {
    cVar6 = '\x02';
  }
  else {
    cVar6 = '\x01';
  }
  if (((((*(char *)(puVar1 + 0xf) == '\0') || (puVar1[0xb] != iVar3)) ||
       (*(char *)(puVar1 + 10) != cVar6)) ||
      ((iVar4 = FUN_000402f4(puVar1[4],param_2), iVar4 == 0 ||
       (iVar4 = FUN_000402f4(*(undefined3 *)((int)puVar1 + 0x13),param_3), iVar4 == 0)))) ||
     ((puVar1[9] != param_4 || (puVar1[6] != param_5)))) {
    *(char *)(puVar1 + 10) = cVar6;
    puVar1[3] = iVar2;
    puVar1[0xb] = iVar3;
    local_2c = (undefined2)param_2;
    *(undefined2 *)(puVar1 + 4) = local_2c;
    uStack_2a = (undefined1)((uint)param_2 >> 0x10);
    *(undefined1 *)((int)puVar1 + 0x12) = uStack_2a;
    local_28 = (undefined2)param_3;
    *(undefined2 *)((int)puVar1 + 0x13) = local_28;
    uStack_26 = (undefined1)((uint)param_3 >> 0x10);
    *(undefined1 *)((int)puVar1 + 0x15) = uStack_26;
    puVar1[6] = param_5;
    puVar1[7] = param_5;
    *puVar1 = 0x62385;
    puVar1[8] = param_5;
    puVar1[9] = param_4;
    FUN_000607d8(puVar1);
    if ((param_1 == 0) || (puVar5 = (undefined4 *)FUN_00040950(param_1), puVar5 == puVar1)) {
      FUN_0004e21c(0);
    }
    *(undefined1 *)(puVar1 + 0xf) = 1;
  }
  return puVar1;
}

