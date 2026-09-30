/* Address: 000372f4; name: FUN_000372f4; body bytes: 242 */

int FUN_000372f4(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined2 local_24;
  undefined2 uStack_22;
  
  if (param_2 != 0) {
    iVar6 = *(int *)(param_1 + 0x18);
    for (uVar4 = 0; uVar4 < (*(ushort *)(iVar6 + 0x12) & 0x1ff); uVar4 = uVar4 + 1 & 0xffff) {
      uVar2 = param_2 - *(int *)(*(int *)(iVar6 + 8) + uVar4 * 0x14);
      if (uVar2 < *(ushort *)(*(int *)(iVar6 + 8) + uVar4 * 0x14 + 4)) {
        iVar5 = *(int *)(iVar6 + 8);
        cVar1 = *(char *)(iVar5 + uVar4 * 0x14 + 0x12);
        if (cVar1 == '\x02') {
          uVar3 = (uint)*(ushort *)(iVar5 + uVar4 * 0x14 + 6);
        }
        else {
          if (cVar1 == '\0') {
            return (uint)*(ushort *)(iVar5 + uVar4 * 0x14 + 6) +
                   (uint)*(byte *)(*(int *)(iVar5 + uVar4 * 0x14 + 0xc) + uVar2);
          }
          uStack_22 = (undefined2)((uint)param_4 >> 0x10);
          if (cVar1 == '\x03') {
            _local_24 = CONCAT22(uStack_22,(short)uVar2);
            iVar7 = uVar4 * 0x14 + 8;
            iVar5 = FUN_00052d7c(&local_24,*(undefined4 *)(*(int *)(iVar6 + 8) + iVar7),
                                 *(undefined2 *)(*(int *)(iVar6 + 8) + uVar4 * 0x14 + 0x10),2,
                                 0x6513d);
            if (iVar5 == 0) {
              return 0;
            }
            uVar2 = iVar5 - *(int *)(*(int *)(iVar6 + 8) + iVar7) >> 1;
            uVar3 = (uint)*(ushort *)(*(int *)(iVar6 + 8) + uVar4 * 0x14 + 6);
          }
          else {
            if (cVar1 != '\x01') {
              return 0;
            }
            _local_24 = CONCAT22(uStack_22,(short)uVar2);
            iVar7 = uVar4 * 0x14 + 8;
            iVar5 = FUN_00052d7c(&local_24,*(undefined4 *)(*(int *)(iVar6 + 8) + iVar7),
                                 *(undefined2 *)(*(int *)(iVar6 + 8) + uVar4 * 0x14 + 0x10),2,
                                 0x6513d);
            if (iVar5 == 0) {
              return 0;
            }
            iVar6 = *(int *)(iVar6 + 8);
            uVar3 = (uint)*(ushort *)(iVar6 + uVar4 * 0x14 + 6);
            uVar2 = (uint)*(ushort *)
                           (*(int *)(iVar6 + uVar4 * 0x14 + 0xc) +
                           (iVar5 - *(int *)(iVar6 + iVar7) >> 1) * 2);
          }
        }
        return uVar3 + uVar2;
      }
    }
  }
  return 0;
}

