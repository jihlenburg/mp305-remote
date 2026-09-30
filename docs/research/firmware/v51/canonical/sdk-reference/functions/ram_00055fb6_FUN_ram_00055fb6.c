/* Address: ram:00055fb6; name: FUN_ram_00055fb6; body bytes: 172 */

void FUN_ram_00055fb6(undefined4 *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  
  gp = 0x20004000;
  if (1 < DAT_ram_20001e04) {
    iVar5 = (uint)*(ushort *)((int)param_1 + 0x1c6) + (uint)*(ushort *)((int)param_1 + 0x1ca) +
            0x271;
    uVar1 = FUN_ram_0006bae2((uint)DAT_ram_20001b8c * iVar5,
                             (int)((longlong)iVar5 * (ulonglong)(uint)DAT_ram_20001b8c >> 0x20),
                             1000000,0);
    for (uVar3 = 1; uVar3 < *(byte *)((int)param_1 + 0x53) - 1; uVar3 = uVar3 + 1) {
      uVar2 = 0xffffffff;
      uVar4 = uVar3 * 0x28 + param_1[0x24];
      piVar6 = (int *)DAT_ram_20001df0;
      while( true ) {
        if ((piVar6 == (int *)0x0) ||
           ((param_1 == piVar6 && (piVar6 = (int *)*param_1, piVar6 == (int *)0x0)))) {
          *(short *)(param_1 + 0x15) = (short)uVar3;
          gp = 0x20004000;
          return;
        }
        if (piVar6[0x23] == param_1[0x23]) {
          uVar7 = piVar6[0x24];
          uVar2 = uVar7 - uVar4;
          if (uVar7 <= uVar4) {
            uVar2 = uVar4 - uVar7;
          }
        }
        if (uVar2 < uVar1) break;
        piVar6 = (int *)*piVar6;
      }
    }
  }
  return;
}

