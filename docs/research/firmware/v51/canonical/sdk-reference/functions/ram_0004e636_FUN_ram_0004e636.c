/* Address: ram:0004e636; name: FUN_ram_0004e636; body bytes: 94 */

void FUN_ram_0004e636(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_0004e38c();
  if ((iVar2 != 0) && (iVar1 = *(int *)(iVar2 + 0x34), iVar1 != 0)) {
    iVar3 = DAT_ram_20001a70;
    if (*(char *)(iVar1 + 2) != '\0') {
      iVar3 = DAT_ram_20001a6c;
    }
    if ((iVar3 != 0) && (*(code **)(iVar3 + 4) != (code *)0x0)) {
      (**(code **)(iVar3 + 4))(iVar1);
    }
    if (*(char *)(iVar1 + 3) == '/') {
      FUN_ram_0004e5a2(*(undefined2 *)(iVar2 + 2),0);
      return;
    }
  }
  return;
}

