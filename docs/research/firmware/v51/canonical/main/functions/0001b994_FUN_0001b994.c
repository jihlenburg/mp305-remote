/* Address: 0001b994; name: FUN_0001b994; body bytes: 168 */

void FUN_0001b994(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  for (uVar3 = 0; uVar3 < (byte)(&DAT_1fffa3f4)[DAT_1fffa408]; uVar3 = uVar3 + 1 & 0xff) {
    FUN_00026470(DAT_1ffe04fc,uVar3,0);
    if (uVar3 == 0) {
      uVar1 = FUN_0004037c(0x261f00);
      uVar2 = FUN_0004b9de(DAT_1ffe04fc,0);
      FUN_0004e8b2(uVar2,uVar1,0);
      uVar1 = FUN_0004037c(0xffa600);
      uVar2 = FUN_0004b9de(DAT_1ffe04fc,0);
      FUN_0004e8e6(uVar2,uVar1,0);
      FUN_0004e538(DAT_1ffe04fc,0);
    }
    if ((((&DAT_1fffa41c)[uVar3 * 3] == 0) && ((&DAT_1fffa414)[uVar3 * 3] != 0)) &&
       (((&DAT_1fffa418)[uVar3 * 3] & 0xffffff) != 0)) {
      DAT_1fffab84 = (&DAT_1fffa418)[uVar3 * 3] & 0xffffff;
      uVar1 = FUN_0004b9de(DAT_1ffe04fc,uVar3);
      uVar1 = FUN_0004b9de(uVar1,3);
      FUN_000499de(uVar1,&DAT_0001ba54,DAT_1fffab84);
    }
  }
  return;
}

