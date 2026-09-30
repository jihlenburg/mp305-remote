/* Address: ram:00041c2a; name: FUN_ram_00041c2a; body bytes: 30 */

void FUN_ram_00041c2a(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  gp = 0x20004000;
  *(undefined4 *)(param_2 + -8) = 0;
  iVar1 = *param_1;
  if (*param_1 != 0) {
    do {
      iVar2 = iVar1;
      iVar1 = *(int *)(iVar2 + -8);
    } while (iVar1 != 0);
    *(int *)(iVar2 + -8) = param_2;
    return;
  }
  *param_1 = param_2;
  return;
}

