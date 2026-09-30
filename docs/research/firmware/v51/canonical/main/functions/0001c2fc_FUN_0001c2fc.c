/* Address: 0001c2fc; name: FUN_0001c2fc; body bytes: 74 */

void FUN_0001c2fc(uint param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  for (; param_1 != 0; param_1 = param_1 >> 1) {
    if ((param_1 & 1) != 0) {
      uVar1 = uVar3 * 8;
      uVar2 = 7 << (uVar1 + 4 & 0xff) | 7 << (uVar1 & 0xff);
      DAT_40050800 = (param_2 << (uVar1 + 4 & 0xff) | param_3 << (uVar1 & 0xff)) & uVar2 |
                     DAT_40050800 & ~uVar2;
    }
    uVar3 = uVar3 + 1 & 0xff;
  }
  return;
}

