/* Address: 00024be0; name: FUN_00024be0; body bytes: 160 */

int FUN_00024be0(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int local_28;
  uint local_24;
  
  local_28 = 0;
  iVar3 = 0;
  local_24 = 0;
  if (param_2 != 0) {
    uVar2 = param_2;
    if (0x7f < param_2) {
      iVar1 = FUN_000632cc(param_2);
      uVar2 = param_2 + (1 << (iVar1 - 5U & 0xff)) + -1;
    }
    FUN_00053566(uVar2,&local_28,&local_24);
    if (local_28 < 0xc) {
      if ((*(uint *)(param_1 + local_28 * 4 + 0x14) & -1 << (local_24 & 0xff)) == 0) {
        if ((*(uint *)(param_1 + 0x10) & -1 << (local_28 + 1U & 0xff)) == 0) {
          return 0;
        }
        local_28 = FUN_000632bc();
        if (*(int *)(param_1 + local_28 * 4 + 0x14) == 0) {
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
      }
      iVar3 = local_28;
      local_24 = FUN_000632bc();
      iVar3 = *(int *)(param_1 + iVar3 * 0x80 + local_24 * 4 + 0x44);
      if (iVar3 != 0) {
        if ((*(uint *)(iVar3 + 4) & 0xfffffffc) < param_2) {
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        FUN_0005b1e8(param_1,iVar3,local_28,local_24);
      }
    }
  }
  return iVar3;
}

