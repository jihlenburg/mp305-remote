/* Address: ram:00055ef4; name: FUN_ram_00055ef4; body bytes: 194 */

void FUN_ram_00055ef4(undefined4 *param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  
  gp = 0x20004000;
  uVar2 = FUN_ram_000428ec(0,4);
  uVar1 = DAT_ram_20001e04;
  *(undefined2 *)(param_1 + 0x15) = uVar2;
  if (1 < uVar1) {
    iVar7 = (uint)*(ushort *)((int)param_1 + 0x1c6) + (uint)*(ushort *)((int)param_1 + 0x1ca) +
            0x271;
    uVar3 = FUN_ram_0006bae2((uint)DAT_ram_20001b8c * iVar7,
                             (int)((longlong)iVar7 * (ulonglong)(uint)DAT_ram_20001b8c >> 0x20),
                             1000000,0);
    uVar4 = (uint)*(ushort *)((int)param_1 + 0x56);
    for (uVar5 = 1; uVar5 < uVar4 - 1; uVar5 = uVar5 + 2) {
      uVar6 = 0xffffffff;
      piVar8 = (int *)DAT_ram_20001df0;
      while( true ) {
        if ((piVar8 == (int *)0x0) ||
           ((param_1 == piVar8 && (piVar8 = (int *)*param_1, piVar8 == (int *)0x0)))) {
          *(short *)(param_1 + 0x15) = (short)uVar5;
          gp = 0x20004000;
          return;
        }
        if ((piVar8[0x23] == uVar4) &&
           (uVar6 = (uVar5 * 0x28 +
                    ((uint)*(ushort *)(param_1 + 0x17) - (uint)*(ushort *)((int)param_1 + 0x3e)) *
                    uVar4 + param_1[0x24]) - piVar8[0x24], uVar4 != 0)) {
          uVar6 = uVar6 % uVar4;
        }
        if (uVar6 < uVar3) break;
        piVar8 = (int *)*piVar8;
      }
    }
  }
  return;
}

