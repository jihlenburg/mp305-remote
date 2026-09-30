/* Address: 0001fd50; name: FUN_0001fd50; body bytes: 180 */

void FUN_0001fd50(void)

{
  uint uVar1;
  uint uVar2;
  char local_128 [256];
  undefined1 local_28 [8];
  
  if (DAT_1fffab1e != '\0') {
    local_28[0] = 0;
    FUN_0001049c(local_128,0x100);
    uVar2 = 0;
    do {
      uVar1 = 0;
      FUN_0001bef8(uVar2 * 0x100 + 0x1f0000,local_128,0x100);
      do {
        if (local_128[uVar1] != '\0') {
          if (local_128[uVar1] != -1) {
            FUN_0001bf3a(uVar1 + uVar2 * 0x100 + 0x1f0000,local_28,1);
            uVar1 = uVar1 + 1 & 0xffff;
            if (uVar1 == 0) {
              uVar2 = uVar2 + 1 & 0xffff;
            }
          }
          FUN_0001bef8(8,&DAT_1fffa018,4);
          if (DAT_1fffa018 < 0xb001) {
            if (DAT_1fffa018 == 0) {
              local_28[0] = 1;
            }
            else {
              local_28[0] = 3;
            }
          }
          else {
            local_28[0] = 7;
          }
          FUN_0001bf3a(uVar1 + uVar2 * 0x100 + 0x1f0000,local_28,1);
          goto LAB_0001fdfa;
        }
        uVar1 = uVar1 + 1 & 0xffff;
      } while (uVar1 < 0x100);
      uVar2 = uVar2 + 1 & 0xffff;
    } while (uVar2 < 0x10);
LAB_0001fdfa:
    DAT_1fffab1e = '\0';
  }
  return;
}

