/* Address: ram:0004cd62; name: FUN_ram_0004cd62; body bytes: 140 */

undefined4 FUN_ram_0004cd62(ushort *param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  
  gp = 0x20004000;
  param_1[2] = 0;
  param_1[3] = 0;
  if ((*(char *)(param_2 + 4) != '\x02') || (*(ushort *)(param_2 + 6) < 4)) {
    return 1;
  }
  uVar1 = **(ushort **)(param_2 + 8);
  if ((uVar1 + 4 == (uint)*(ushort *)(param_2 + 6)) &&
     ((uVar2 = (*(ushort **)(param_2 + 8))[1], (ushort)(uVar2 - 4) < 4 ||
      (iVar4 = FUN_ram_0004c344(uVar2), iVar4 != 0)))) {
    uVar3 = *(undefined4 *)(param_2 + 8);
    param_1[1] = uVar1;
    *param_1 = uVar2;
    uVar3 = FUN_ram_00041bf2(uVar3,0xfffffffc);
    *(undefined4 *)(param_1 + 2) = uVar3;
    gp = 0x20004000;
    return 0;
  }
  return 1;
}

