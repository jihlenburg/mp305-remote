/* Address: 00059ed0; name: FUN_00059ed0; body bytes: 106 */

void FUN_00059ed0(int param_1)

{
  char cVar1;
  int iVar2;
  
  enter_critical();
  cVar1 = *(char *)(param_1 + 0x45);
  while (('\0' < cVar1 && (*(int *)(param_1 + 0x24) != 0))) {
    iVar2 = FUN_00066ea4(param_1 + 0x24);
    if (iVar2 != 0) {
      FUN_000659bc();
    }
    cVar1 = cVar1 + -1;
  }
  *(undefined1 *)(param_1 + 0x45) = 0xff;
  exit_critical();
  enter_critical();
  cVar1 = *(char *)(param_1 + 0x44);
  while (('\0' < cVar1 && (*(int *)(param_1 + 0x10) != 0))) {
    iVar2 = FUN_00066ea4(param_1 + 0x10);
    if (iVar2 != 0) {
      FUN_000659bc();
    }
    cVar1 = cVar1 + -1;
  }
  *(undefined1 *)(param_1 + 0x44) = 0xff;
  exit_critical();
  return;
}

