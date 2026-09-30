/* Address: ram:0004d4e2; name: FUN_ram_0004d4e2; body bytes: 372 */

undefined4 FUN_ram_0004d4e2(uint param_1,undefined2 *param_2)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  short sVar7;
  uint uVar8;
  undefined2 uStack_28;
  short sStack_26;
  undefined4 uStack_24;
  
  gp = 0x20004000;
  iVar4 = FUN_ram_0004c344(*param_2);
  if (((iVar4 != 0) && (iVar3 = *(int *)(iVar4 + 0xc), iVar3 != 0)) &&
     (*(ushort *)(iVar4 + 6) == param_1)) {
    if (*(short *)(iVar3 + 8) == 0) {
      uVar5 = 6;
    }
    else {
      sVar7 = *(short *)(iVar3 + 8) + -1;
      sVar1 = *(short *)(DAT_ram_20001cc4 + (uint)*(byte *)(iVar3 + 0x1c) * 0x10 + 6);
      *(short *)(iVar3 + 8) = sVar7;
      if (sVar1 == sVar7) {
        FUN_ram_0004d270(iVar4,99);
      }
      if (*(int *)(iVar3 + 0x14) == 0) {
        uVar2 = **(ushort **)(param_2 + 2);
        if (uVar2 + 2 == (uint)(ushort)param_2[1]) {
          uVar5 = FUN_ram_00041bf2(*(ushort **)(param_2 + 2),0xfffffffe);
          *(undefined4 *)(param_2 + 2) = uVar5;
          param_2[1] = uVar2;
          iVar6 = FUN_ram_0004d198(*(undefined1 *)(iVar4 + 8),param_1,param_2);
          if (iVar6 == 0) {
            gp = 0x20004000;
            return 0;
          }
        }
        else {
          uVar5 = FUN_ram_20000040((uint)uVar2,0x4c01);
          *(undefined4 *)(iVar3 + 0x14) = uVar5;
          uVar5 = *(undefined4 *)(param_2 + 2);
          *(ushort *)(iVar3 + 0x18) = uVar2;
          uVar5 = FUN_ram_00041bf2(uVar5,0xfffffffe);
          *(undefined4 *)(param_2 + 2) = uVar5;
          param_2[1] = param_2[1] + -2;
        }
      }
      if (*(int *)(iVar3 + 0x14) == 0) {
        uVar5 = 9;
      }
      else {
        uVar8 = (uint)(ushort)param_2[1] + (uint)*(ushort *)(iVar3 + 0x1a);
        if (*(ushort *)(iVar3 + 0x18) < uVar8) {
          uVar5 = 4;
        }
        else {
          uVar5 = 5;
          if (uVar8 <= *(ushort *)(DAT_ram_20001cc4 + (uint)*(byte *)(iVar3 + 0x1c) * 0x10 + 2)) {
            tmos_memcpy(*(int *)(iVar3 + 0x14) + (uint)*(ushort *)(iVar3 + 0x1a),
                        *(undefined4 *)(param_2 + 2));
            sStack_26 = param_2[1] + *(short *)(iVar3 + 0x1a);
            *(short *)(iVar3 + 0x1a) = sStack_26;
            if (sStack_26 != *(short *)(iVar3 + 0x18)) {
              gp = 0x20004000;
              return 1;
            }
            uStack_28 = *(undefined2 *)(iVar4 + 2);
            uStack_24 = *(undefined4 *)(iVar3 + 0x14);
            iVar4 = FUN_ram_0004d198(*(undefined1 *)(iVar4 + 8),param_1,&uStack_28);
            if (iVar4 != 0) {
              FUN_ram_20000104(*(undefined4 *)(iVar3 + 0x14));
            }
            *(undefined4 *)(iVar3 + 0x14) = 0;
            *(undefined4 *)(iVar3 + 0x18) = 0;
            gp = 0x20004000;
            return 1;
          }
        }
      }
    }
    FUN_ram_0004c46e(iVar4,uVar5);
  }
  return 1;
}

