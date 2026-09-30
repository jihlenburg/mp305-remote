/* Address: 0004ef90; name: FUN_0004ef90; body bytes: 52 */

void FUN_0004ef90(void)

{
  int iVar1;
  
  if (DAT_2003a480 == '\0') {
    DAT_2003a480 = 1;
    iVar1 = FUN_0004bc94();
    while( true ) {
      if (-1 < (int)((uint)*(ushort *)(iVar1 + 0x2a) << 0x1d)) break;
      *(ushort *)(iVar1 + 0x2a) = *(ushort *)(iVar1 + 0x2a) & 0xfffb;
      FUN_0003bf62(iVar1);
    }
    DAT_2003a480 = '\0';
  }
  return;
}

