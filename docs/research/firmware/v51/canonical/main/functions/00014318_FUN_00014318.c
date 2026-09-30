/* Address: 00014318; name: FUN_00014318; body bytes: 166 */

void FUN_00014318(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  char local_28 [12];
  
  local_28[0] = '\0';
  local_28[1] = '\0';
  local_28[2] = '\0';
  local_28[3] = '\0';
  local_28[4] = '\0';
  local_28[5] = '\0';
  local_28[6] = '\0';
  local_28[7] = '\0';
  local_28[8] = '\0';
  local_28[9] = '\0';
  local_28[10] = '\0';
  local_28[0xb] = '\0';
  if (DAT_1ffe01cc == '\0') {
    FUN_0001bef8(0x161000,&DAT_1fffa354,0xc0);
    uVar1 = 0;
    do {
      uVar3 = (uint)(byte)(&DAT_1fffa3fe)[uVar1];
      if (local_28[uVar3] != '\0') goto LAB_0001437c;
      if (uVar3 != 0) {
        local_28[uVar3] = '\x01';
      }
      uVar1 = uVar1 + 1 & 0xff;
    } while (uVar1 < 10);
  }
  if (((DAT_1fffa40c == -0x55aa33cd) && (iVar2 = FUN_000159cc(), iVar2 == DAT_1fffa410)) &&
     (DAT_1ffe01cc == '\0')) {
    FUN_0001bef8((uint)DAT_1fffa408 * 0x1000 + 0x162000,&DAT_1fffa414,0x4b0);
  }
  else {
LAB_0001437c:
    DAT_1fffa40c = -0x55aa33cd;
    DAT_1fffa408 = 0;
    FUN_000143d0();
    DAT_1fffa410 = FUN_000159cc();
    FUN_0001bdf6(0x161000);
    FUN_0001bf3a(0x161000,&DAT_1fffa354,0xc0);
  }
  return;
}

