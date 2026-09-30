/* Address: ram:00052640; name: thunk_FUN_ram_000680f4; body bytes: 4 */

undefined4 thunk_FUN_ram_000680f4(undefined2 *param_1)

{
  char cVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  
  gp = 0x20004000;
  iVar4 = FUN_ram_00057ba2(*param_1);
  uVar5 = 2;
  if (iVar4 != 0) {
    cVar1 = *(char *)((int)param_1 + 3);
    uVar5 = 0x12;
    if ((((cVar1 < '\x01') && (-0x60 < *(char *)(param_1 + 1))) &&
        (cVar2 = *(char *)((int)param_1 + 5), cVar2 < '\a')) &&
       (cVar3 = *(char *)(param_1 + 2), -0x11 < cVar3)) {
      *(char *)(iVar4 + 0x162) = *(char *)(param_1 + 1);
      *(char *)(iVar4 + 0x163) = cVar1;
      *(char *)(iVar4 + 0x15e) = cVar3;
      *(char *)(iVar4 + 0x15f) = cVar2;
      uVar5 = 0;
    }
  }
  return uVar5;
}

