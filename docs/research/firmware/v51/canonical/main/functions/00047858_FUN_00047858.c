/* Address: 00047858; name: FUN_00047858; body bytes: 164 */

ushort * FUN_00047858(int param_1,ushort *param_2)

{
  uint uVar1;
  int iVar2;
  ushort *puVar3;
  
  if (param_2 == (ushort *)0x0) {
    return (ushort *)0x0;
  }
  puVar3 = param_2;
  if ((((*(char *)(param_1 + 4) != '\0') && (*param_2 >> 8 != 0x14)) &&
      (uVar1 = FUN_00041788(param_2[2]), param_2[4] != uVar1)) &&
     (iVar2 = FUN_000410a2(param_2,uVar1), iVar2 != 1)) {
    puVar3 = (ushort *)
             FUN_0004137c(&DAT_2003a518,*(uint *)(param_2 + 2) & 0xffff,
                          *(uint *)(param_2 + 2) >> 0x10,*param_2 >> 8,uVar1);
    if (puVar3 == (ushort *)0x0) {
      return (ushort *)0x0;
    }
    FUN_0004126c(puVar3,0,param_2);
  }
  if (((*(char *)(param_1 + 5) != '\0') && (3 < (*puVar3 >> 8) - 0xb)) &&
     ((iVar2 = FUN_0004035a(), iVar2 != 0 && (iVar2 = FUN_00041546(puVar3,1), iVar2 == 0)))) {
    iVar2 = FUN_00041546(puVar3,0x20);
    if ((iVar2 == 0) &&
       (puVar3 = (ushort *)FUN_0004142a(&DAT_2003a518,puVar3), puVar3 == (ushort *)0x0)) {
      return (ushort *)0x0;
    }
    FUN_00041604(puVar3);
  }
  return puVar3;
}

