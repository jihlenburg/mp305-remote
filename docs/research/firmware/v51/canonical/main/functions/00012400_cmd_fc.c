/* Address: 00012400; name: cmd_fc; body bytes: 270 */

undefined4 cmd_fc(int param_1,undefined1 *param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  char local_140 [256];
  undefined1 local_40 [4];
  undefined4 local_3c [2];
  int iStack_34;
  undefined1 *puStack_30;
  int local_2c;
  undefined4 uStack_28;
  
  local_3c[0] = 0xaa55cc33;
  local_40[0] = 0;
  iStack_34 = param_1;
  puStack_30 = param_2;
  local_2c = param_3;
  uStack_28 = param_4;
  FUN_0001049c(local_140,0x100);
  if (*(char *)(param_1 + 1) == -0x36) {
    if (DAT_1fffa010 != 0) {
      FUN_0001bf3a(0,&DAT_1fffa010,4);
      FUN_0001bf3a(4,&DAT_1fffa014);
      FUN_0001bf3a(8,&DAT_1fffa018,4);
      FUN_0001bf3a(0xc,local_3c,4);
      uVar3 = 0;
      do {
        uVar2 = 0;
        FUN_0001bef8(uVar3 * 0x100 + 0x1f0000,local_140,0x100);
        do {
          if (local_140[uVar2] != '\0') {
            if (local_140[uVar2] != -1) {
              FUN_0001bf3a(uVar2 + uVar3 * 0x100 + 0x1f0000,local_40,1);
              uVar2 = uVar2 + 1 & 0xffff;
              if (uVar2 == 0) {
                uVar3 = uVar3 + 1 & 0xffff;
              }
            }
            if (DAT_1fffa018 < 0xb001) {
              if (DAT_1fffa018 == 0) {
                local_40[0] = 1;
              }
              else {
                local_40[0] = 3;
              }
            }
            else {
              local_40[0] = 7;
            }
            FUN_0001bf3a(uVar2 + uVar3 * 0x100 + 0x1f0000,local_40,1);
            goto LAB_000124ea;
          }
          uVar2 = uVar2 + 1 & 0xffff;
        } while (uVar2 < 0x100);
        uVar3 = uVar3 + 1 & 0xffff;
      } while (uVar3 < 0x10);
    }
LAB_000124ea:
    DAT_1fffa00d = 1;
    DAT_1fffa00c = 0;
    *param_2 = 0xfd;
    param_2[1] = 0;
    uVar1 = 2;
    if (local_2c == 6) {
      param_2[2] = 0x31;
      uVar1 = 3;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

