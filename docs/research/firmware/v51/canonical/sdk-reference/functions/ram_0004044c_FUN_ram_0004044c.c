/* Address: ram:0004044c; name: FUN_ram_0004044c; body bytes: 32 */

void FUN_ram_0004044c(int param_1,int param_2,int param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  
  gp = 0x20004000;
  if (((param_1 != 0) && (param_2 != 0)) && (param_3 != 0)) {
    iVar3 = 0;
    do {
      puVar1 = (undefined1 *)(param_2 + iVar3);
      puVar2 = (undefined1 *)(param_1 + iVar3);
      iVar3 = iVar3 + 1;
      *puVar2 = *puVar1;
    } while (param_3 != iVar3);
  }
  return;
}

