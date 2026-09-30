/* Address: 00046faa; name: FUN_00046faa; body bytes: 292 */

void FUN_00046faa(undefined2 *param_1,int param_2,int param_3,undefined2 *param_4,
                 undefined1 *param_5)

{
  short sVar1;
  ushort uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  uint uVar5;
  ushort *puVar6;
  uint uVar7;
  int iVar8;
  undefined2 local_20;
  undefined1 uStack_1e;
  
  if ((int)(param_2 * (uint)*(byte *)(param_1 + 2)) >> 8 < param_3) {
    uVar7 = (uint)*(byte *)(param_1 + 5);
    if (param_3 < (int)(param_2 * (uint)*(byte *)((int)param_1 + uVar7 * 5 + -1)) >> 8) {
      uVar5 = 1;
      do {
        if (uVar7 <= uVar5) {
LAB_000470cc:
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        if (param_3 <= (int)(param_2 * (uint)*(byte *)((int)param_1 + uVar5 * 5 + 4)) >> 8) {
          if (uVar5 != 0) {
            puVar6 = (ushort *)(uVar5 * 5 + (int)param_1);
            iVar8 = (int)(param_2 * (uint)*(byte *)((int)puVar6 + -1)) >> 8;
            uVar2 = (ushort)(((param_3 - iVar8) * 0xff) /
                            (((int)(param_2 * (uint)(byte)puVar6[2]) >> 8) - iVar8)) & 0xff;
            sVar1 = 0xff - uVar2;
            uVar3 = FUN_000403bc((((int)(short)(ushort)*(byte *)((int)puVar6 + -3) * (int)sVar1 +
                                  (int)(short)(ushort)(byte)puVar6[1] * (int)(short)uVar2) * 0x8081
                                 & 0x7fffffffU) >> 0x17,
                                 (((int)(short)(*(ushort *)((int)puVar6 + -5) >> 8) * (int)sVar1 +
                                  (int)(short)(*puVar6 >> 8) * (int)(short)uVar2) * 0x8081 &
                                 0x7fffffffU) >> 0x17,
                                 (((int)(short)(*(ushort *)((int)puVar6 + -5) & 0xff) * (int)sVar1 +
                                  (int)(short)(*puVar6 & 0xff) * (int)(short)uVar2) * 0x8081 &
                                 0x7fffffffU) >> 0x17);
            local_20 = (undefined2)uVar3;
            *param_4 = local_20;
            uStack_1e = (undefined1)((uint)uVar3 >> 0x10);
            *(undefined1 *)(param_4 + 1) = uStack_1e;
            uVar4 = (undefined1)
                    ((uint)(((int)(short)(ushort)(byte)puVar6[-1] * (int)sVar1 +
                            (int)(short)(ushort)*(byte *)((int)puVar6 + 3) * (int)(short)uVar2) *
                           0x8081) >> 0x17);
            goto LAB_000470bc;
          }
          goto LAB_000470cc;
        }
        uVar5 = uVar5 + 1 & 0xff;
      } while( true );
    }
    uVar4 = *(undefined1 *)((int)param_1 + uVar7 * 5 + -3);
    *param_4 = *(undefined2 *)((int)param_1 + uVar7 * 5 + -5);
    *(undefined1 *)(param_4 + 1) = uVar4;
    uVar4 = *(undefined1 *)((int)param_1 + (uint)*(byte *)(param_1 + 5) * 5 + -2);
  }
  else {
    uVar4 = *(undefined1 *)(param_1 + 1);
    *param_4 = *param_1;
    *(undefined1 *)(param_4 + 1) = uVar4;
    uVar4 = *(undefined1 *)((int)param_1 + 3);
  }
LAB_000470bc:
  *param_5 = uVar4;
  return;
}

