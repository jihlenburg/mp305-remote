/* Address: 00012d10; name: FUN_00012d10; body bytes: 232 */

int FUN_00012d10(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint local_48;
  uint local_40;
  
  uVar2 = DAT_2003a60c >> ((DAT_40054020 & 0x7ffffff) >> 0x18);
  iVar1 = -3;
  if ((param_1 != 0) && (param_2 != 0)) {
    if ((DAT_4001c804 & 2) == 2) {
      local_40 = 0;
      iVar1 = 0;
      uVar3 = DAT_4001c80c & 3;
      uVar4 = DAT_4001c818 & 0xf00;
      do {
        if (param_2 <= local_40) break;
        for (local_48 = 0; local_48 < uVar3 + 1; local_48 = local_48 + 1) {
          if (uVar4 < 0x401) {
            DAT_4001c800 = (uint)*(byte *)(param_1 + local_40);
          }
          else if (uVar4 < 0xc01) {
            DAT_4001c800 = (uint)*(ushort *)(param_1 + local_40 * 2);
          }
          else {
            DAT_4001c800 = *(uint *)(param_1 + local_40 * 4);
          }
          local_40 = local_40 + 1;
        }
        iVar1 = FUN_0001c2e0(&DAT_4001c800,0x20,0x20,uVar2);
      } while (iVar1 == 0);
      if (((int)(DAT_4001c804 << 0x1c) < 0) && (iVar1 == 0)) {
        iVar1 = FUN_0001c2e0(&DAT_4001c800,2,0,uVar2);
        return iVar1;
      }
      return iVar1;
    }
    iVar1 = FUN_0001c162(&DAT_4001c800,param_1,0,param_2,uVar2);
  }
  return iVar1;
}

