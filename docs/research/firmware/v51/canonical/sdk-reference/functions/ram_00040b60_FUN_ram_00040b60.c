/* Address: ram:00040b60; name: FUN_ram_00040b60; body bytes: 166 */

void FUN_ram_00040b60(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  gp = 0x20004000;
  uVar1 = (uint)*(byte *)(param_1 + 0x137) + (uint)*(byte *)(param_1 + 0x33) & 0xff;
  if (0x24 < uVar1) {
    uVar1 = uVar1 - 0x25 & 0xff;
  }
  uVar6 = *(undefined4 *)(param_1 + 0x138);
  uVar7 = *(undefined4 *)(param_1 + 0x13c);
  *(char *)(param_1 + 0x137) = (char)uVar1;
  uVar2 = (*(code *)&SUB_ram_e00abcfa)(uVar6,uVar7,uVar1);
  if ((uVar2 & 1) == 0) {
    uVar4 = 0;
    uVar5 = 0;
    uVar2 = uVar1;
    if (*(byte *)(param_1 + 0x12d) != 0) {
      uVar2 = uVar1 % (uint)*(byte *)(param_1 + 0x12d);
    }
    do {
      uVar3 = (*(code *)&SUB_ram_e00abcfa)(uVar6,uVar7,uVar4);
      if ((uVar3 & 1) != 0) {
        if (uVar5 == uVar2) {
          uVar1 = uVar4 & 0xff;
          break;
        }
        uVar5 = (int)((uVar5 + 1) * 0x1000000) >> 0x18;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 != 0x25);
  }
  *(char *)(param_1 + 0x136) = (char)uVar1;
  return;
}

