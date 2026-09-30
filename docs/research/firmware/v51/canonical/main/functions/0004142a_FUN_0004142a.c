/* Address: 0004142a; name: FUN_0004142a; body bytes: 68 */

undefined4 * FUN_0004142a(undefined4 param_1,ushort *param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  
  puVar1 = (undefined4 *)
           FUN_0004137c(param_1,*(uint *)(param_2 + 2) & 0xffff,*(uint *)(param_2 + 2) >> 0x10,
                        *param_2 >> 8,param_2[4]);
  if (puVar1 != (undefined4 *)0x0) {
    *(short *)((int)puVar1 + 2) = (short)((uint)*(undefined4 *)param_2 >> 0x10);
    *(ushort *)((int)puVar1 + 2) = (ushort)((uint)*puVar1 >> 0x10) | 0x30;
    uVar2 = puVar1[3];
    if (*(uint *)(param_2 + 6) < (uint)puVar1[3]) {
      uVar2 = *(uint *)(param_2 + 6);
    }
    FUN_0004a404(puVar1[4],*(undefined4 *)(param_2 + 8),uVar2);
  }
  return puVar1;
}

