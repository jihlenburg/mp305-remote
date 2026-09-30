/* Address: ram:00056856; name: LL_GetNumberOfUnAckPacket; body bytes: 34 */

int LL_GetNumberOfUnAckPacket(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    iVar2 = -1;
  }
  else {
    iVar2 = 0;
    for (piVar3 = *(int **)(iVar1 + 0x118); piVar3 != (int *)0x0; piVar3 = (int *)*piVar3) {
      iVar2 = iVar2 + 1;
    }
  }
  return iVar2;
}

