/* Address: ram:20000996; name: FUN_ram_20000996; body bytes: 1 */

/* WARNING: Removing unreachable block (ram,0x20000b94) */

void FUN_ram_20000996(int param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined1 uVar9;
  
  gp = 0x20004000;
  uVar4 = (*(uint *)(param_1 + 0x98) >> 0x10 ^ *(uint *)(param_1 + 0x98)) & 0xffff;
  uVar3 = *(ushort *)(param_1 + 0x3e) ^ uVar4;
  uVar2 = uVar3 >> 8;
  uVar7 = *(undefined4 *)(param_1 + 0x138);
  uVar8 = *(undefined4 *)(param_1 + 0x13c);
  uVar3 = ((int)uVar3 >> 7 & 1U | (int)uVar3 >> 5 & 2U | (int)uVar3 >> 3 & 4U | (int)uVar3 >> 1 & 8U
           | (uVar3 & 8) << 1 | (uVar3 & 4) << 3 | (uVar3 & 2) << 5 | (uVar3 & 1) << 7 |
          ((int)uVar2 >> 5 & 2U | (int)uVar2 >> 3 & 4U | (int)uVar2 >> 7 | (int)uVar2 >> 1 & 8U |
           (uVar2 & 8) << 1 | (uVar2 & 4) << 3 | (uVar2 & 2) << 5 | (uVar2 & 1) << 7) << 8) * 0x11 +
          uVar4;
  uVar5 = uVar3 & 0xffff;
  uVar2 = uVar5 >> 8;
  uVar3 = ((int)uVar5 >> 7 & 1U | (int)uVar5 >> 5 & 2U | (int)uVar5 >> 3 & 4U | (int)uVar5 >> 1 & 8U
           | (uVar3 & 8) << 1 | (uVar3 & 4) << 3 | (uVar3 & 2) << 5 | (uVar3 & 1) << 7 |
          ((int)uVar2 >> 5 & 2U | (int)uVar2 >> 3 & 4U | (int)uVar2 >> 7 | (int)uVar2 >> 1 & 8U |
           (uVar2 & 8) << 1 | (uVar2 & 4) << 3 | (uVar2 & 2) << 5 | (uVar2 & 1) << 7) << 8) * 0x11 +
          uVar4;
  uVar5 = uVar3 & 0xffff;
  uVar2 = uVar5 >> 8;
  uVar2 = (uVar4 ^ ((uVar3 & 1) << 7 |
                    (int)uVar5 >> 7 & 1U | (int)uVar5 >> 5 & 2U | (int)uVar5 >> 3 & 4U |
                    (int)uVar5 >> 1 & 8U | (uVar3 & 8) << 1 | (uVar3 & 4) << 3 | (uVar3 & 2) << 5 |
                   ((int)uVar2 >> 5 & 2U | (int)uVar2 >> 3 & 4U | (int)uVar2 >> 7 |
                    (int)uVar2 >> 1 & 8U | (uVar2 & 8) << 1 | (uVar2 & 4) << 3 | (uVar2 & 2) << 5 |
                   (uVar2 & 1) << 7) << 8) * 0x11 + uVar4) & 0xffff;
  uVar9 = (undefined1)(uVar2 % 0x25);
  uVar3 = FUN_ram_0006ba8a(uVar7,uVar8);
  if ((uVar3 & 1) == 0) {
    bVar1 = *(byte *)(param_1 + 0x12d);
    iVar6 = 0;
    uVar3 = 0;
    do {
      uVar4 = FUN_ram_0006ba8a(uVar7,uVar8,iVar6);
      if ((uVar4 & 1) != 0) {
        if (bVar1 * uVar2 >> 0x10 == uVar3) {
          uVar9 = (undefined1)iVar6;
          break;
        }
        uVar3 = uVar3 + 1 & 0xff;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 != 0x25);
  }
  *(undefined1 *)(param_1 + 0x136) = uVar9;
  return;
}

