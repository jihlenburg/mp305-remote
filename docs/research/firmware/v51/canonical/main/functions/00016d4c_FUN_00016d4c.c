/* Address: 00016d4c; name: FUN_00016d4c; body bytes: 106 */

undefined4 FUN_00016d4c(ushort *param_1)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint *puVar4;
  
  uVar3 = 0xfffffffd;
  if (param_1 != (ushort *)0x0) {
    uVar1 = *param_1;
    uVar2 = (uint)(short)param_1[1];
    if ((((uint)(uVar1 >> 5) * 6 + 0x20 <= uVar2) && (uVar2 <= (uint)(uVar1 >> 5) * 6 + 0x25)) ||
       (uVar2 < 0x20)) {
      puVar4 = (uint *)(&DAT_4005105c + uVar2 * 4);
      uVar3 = 0;
      if ((*puVar4 & 0x1ff) == 0x1ff) {
        *puVar4 = (uint)uVar1;
        (&DAT_1ffe0b5c)[(short)param_1[1]] = *(undefined4 *)(param_1 + 2);
      }
      else if ((uint)uVar1 == (*puVar4 & 0x1ff)) {
        (&DAT_1ffe0b5c)[uVar2] = *(undefined4 *)(param_1 + 2);
      }
      else {
        uVar3 = 0xfffffffe;
      }
    }
  }
  return uVar3;
}

