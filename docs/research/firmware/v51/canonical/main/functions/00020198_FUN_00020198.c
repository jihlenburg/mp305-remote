/* Address: 00020198; name: FUN_00020198; body bytes: 252 */

uint FUN_00020198(void)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  longlong in_d0;
  undefined8 uVar4;
  uint local_20;
  uint uStack_1c;
  
  local_20 = (uint)in_d0;
  uStack_1c = (uint)((ulonglong)in_d0 >> 0x20);
  uVar1 = (uStack_1c & 0x7fffffff) >> 0x14;
  uVar2 = uVar1 - 0x3ff;
  if (0x13 < (int)uVar2) {
    cVar3 = 0x32 < uVar2;
    if (0x33 < (int)uVar2) {
      return local_20;
    }
    uVar1 = 0xffffffff >> (uVar1 - 0x413 & 0xff);
    if ((local_20 & uVar1) == 0) {
      return local_20;
    }
    uVar4 = FUN_00010836(local_20,uStack_1c,0x8800759c,0x7e37e43c);
    FUN_00010b18((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),0,0);
    if (cVar3 != '\0') {
      return local_20;
    }
    if ((0 < (int)uStack_1c) && (uVar2 != 0x14)) {
      local_20 = (1 << (0x34 - uVar2 & 0xff)) + local_20;
    }
    return local_20 & ~uVar1;
  }
  cVar3 = '\x01';
  if ((int)uVar2 < 0) {
    uVar4 = FUN_000106ee(local_20,uStack_1c,0x8800759c,0x7e37e43c);
    FUN_00010b18((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),0,0);
    if (cVar3 != '\0') {
      return local_20;
    }
    if (in_d0 < 0) {
      return 0;
    }
    if (uStack_1c == 0 && local_20 == 0) {
      return local_20;
    }
  }
  else {
    if ((uStack_1c & 0xfffffU >> (uVar2 & 0xff)) == 0 && local_20 == 0) {
      return local_20;
    }
    uVar4 = FUN_000106ee(local_20,uStack_1c,0x8800759c,0x7e37e43c);
    FUN_00010b18((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),0,0);
    if (cVar3 != '\0') {
      return local_20;
    }
  }
  return 0;
}

