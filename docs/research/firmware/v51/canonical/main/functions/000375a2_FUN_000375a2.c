/* Address: 000375a2; name: FUN_000375a2; body bytes: 60 */

byte FUN_000375a2(int param_1)

{
  int iVar1;
  byte bVar2;
  
  bVar2 = (int)((uint)*(byte *)(param_1 + 0x5c) << 0x1b) < 0;
  iVar1 = FUN_0004cbea(param_1,0);
  if (((iVar1 == 0x3fffffff) && (iVar1 = FUN_0004c75c(param_1,0), iVar1 == 0x1fffffff)) &&
     (-1 < (int)((uint)*(ushort *)(param_1 + 0x2a) << 0x14))) {
    bVar2 = bVar2 | 2;
  }
  return bVar2;
}

