/* Address: 0001df40; name: FUN_0001df40; body bytes: 98 */

void FUN_0001df40(void)

{
  int iVar1;
  
  DAT_1fff8f34 = (((DAT_1fff8f34 & 0xf1ff) + 0x200 & 0xfe3f) + 0xc0 & 0xffc7) + 0x18 | 7;
  iVar1 = FUN_00016c9a(0);
  if (iVar1 == 0) {
    DAT_1fff8f2c = 0x43505556;
    DAT_1fff8f30 = 0x45a2c2ab;
    DAT_1fff8f26 = 0x800;
    iVar1 = FUN_00016c9a(5);
    if (iVar1 == 0) {
      DAT_1fff8f36 = DAT_1fff8f36 | 0x400;
      iVar1 = FUN_00016c9a(6);
      if (iVar1 == 0) {
        DAT_1fff8f24 = 1;
      }
    }
  }
  return;
}

