/* Address: 0003e64c; name: FUN_0003e64c; body bytes: 410 */

/* Recovered from stored Thumb pointer at 0003e63c; callback identification is inferred until
   reviewed. */

int FUN_0003e64c(undefined4 param_1,int param_2)

{
  bool bVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  uint uVar7;
  int iVar8;
  undefined4 local_58;
  undefined4 local_54;
  undefined1 local_50;
  uint uStack_40;
  uint local_3c;
  undefined2 local_38;
  
  iVar8 = 0;
  bVar1 = false;
  if (*(char *)(param_2 + 0x10) == '\x01') {
    uVar2 = FUN_00046ca0(*(undefined4 *)(param_2 + 0xc));
    iVar5 = thunk_FUN_00050a1a(uVar2,&DAT_0003e7e8);
    if ((iVar5 == 0) && (piVar3 = (int *)FUN_000372dc(param_2), piVar3 != (int *)0x0)) {
      *(int **)(param_2 + 0x48) = piVar3;
      iVar5 = FUN_0004a318(0xc);
      if (iVar5 != 0) {
        iVar4 = FUN_00046cd8(iVar5,*(undefined4 *)(param_2 + 0xc),2);
        if (iVar4 == 0) {
          *piVar3 = iVar5;
          uVar7 = (*(uint *)(param_2 + 0x20) & 0xffff) >> 8;
          if (-1 < (int)((*(uint *)(param_2 + 0x20) >> 0x10) << 0x1c)) {
            if (3 < uVar7 - 7) {
              if (uVar7 - 0xb < 4) goto LAB_0003e6c0;
              goto LAB_0003e77e;
            }
            goto LAB_0003e702;
          }
          goto LAB_0003e708;
        }
        FUN_00046bec(iVar5);
      }
LAB_0003e7de:
      FUN_00036b0c(param_2);
    }
    iVar8 = 0;
  }
  else {
    if (*(char *)(param_2 + 0x10) == '\0') {
      puVar6 = *(uint **)(param_2 + 0xc);
      if (puVar6[4] == 0) {
        return 0;
      }
      uVar7 = (uint)(ushort)((ushort)*puVar6 >> 8);
      if (-1 < (int)((*(uint *)(param_2 + 0x20) >> 0x10) << 0x1c)) {
        if (3 < uVar7 - 7) {
          if (uVar7 - 0xb < 4) {
            iVar8 = FUN_000372dc(param_2);
            if (iVar8 == 0) {
              return 0;
            }
LAB_0003e6c0:
            iVar8 = FUN_00027dcc(param_1,param_2);
            goto LAB_0003e6d4;
          }
          iVar8 = FUN_000372dc(param_2);
          if (-1 < (int)((*puVar6 >> 0x10) << 0x1b)) {
            if ((ushort)puVar6[2] == 0) {
              FUN_0001046a(&uStack_40,puVar6,0x18);
              iVar5 = FUN_00040314(uVar7);
              local_38 = (undefined2)((local_3c & 0xffff) * iVar5 + 7 >> 3);
              puVar6 = &uStack_40;
            }
            FUN_00041498((uint *)(iVar8 + 0x24),puVar6);
            puVar6 = (uint *)(iVar8 + 0x24);
          }
          *(uint **)(param_2 + 0x2c) = puVar6;
          if ((ushort)puVar6[2] == 0) {
            *(ushort *)(puVar6 + 2) = *(ushort *)(param_2 + 0x28);
          }
          bVar1 = true;
LAB_0003e77e:
          iVar8 = *(int *)(param_2 + 0x2c);
          if (iVar8 == 0) {
            return 1;
          }
          iVar5 = FUN_00047858(param_2,iVar8);
          if (iVar5 != 0) {
            if (iVar5 == iVar8) {
              *(int *)(param_2 + 0x2c) = iVar5;
              if (bVar1) {
                return 1;
              }
            }
            else {
              FUN_00036b0c(param_2);
              iVar8 = FUN_000372dc(param_2);
              *(int *)(iVar8 + 0x1c) = iVar5;
              *(int *)(param_2 + 0x2c) = iVar5;
            }
            if ((*(char *)(param_2 + 6) != '\0') || (iVar8 = FUN_00047614(), iVar8 == 0)) {
              return 1;
            }
            local_50 = *(undefined1 *)(param_2 + 0x10);
            local_54 = *(undefined4 *)(param_2 + 0xc);
            local_58 = *(undefined4 *)(*(int *)(param_2 + 0x2c) + 0xc);
            iVar8 = FUN_000476b0(param_1,&local_58,*(int *)(param_2 + 0x2c),
                                 *(undefined4 *)(param_2 + 0x48));
            if (iVar8 != 0) {
              *(int *)(param_2 + 0x44) = iVar8;
              iVar8 = FUN_000372dc(param_2);
              *(undefined4 *)(iVar8 + 0x1c) = 0;
              return 1;
            }
          }
          goto LAB_0003e7de;
        }
        iVar5 = FUN_000372dc(param_2);
        if (iVar5 == 0) {
          return 0;
        }
LAB_0003e702:
        if (*(char *)(param_2 + 7) == '\0') {
          iVar8 = FUN_00027ee0(param_1,param_2);
LAB_0003e6d4:
          if (iVar8 == 1) goto LAB_0003e77e;
        }
      }
    }
LAB_0003e708:
    FUN_00036b0c(param_2);
  }
  return iVar8;
}

