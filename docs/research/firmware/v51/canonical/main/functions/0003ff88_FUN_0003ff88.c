/* Address: 0003ff88; name: FUN_0003ff88; body bytes: 192 */

void FUN_0003ff88(undefined4 param_1,undefined2 *param_2,undefined2 *param_3)

{
  byte bVar1;
  byte bVar2;
  undefined2 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 local_28;
  undefined2 local_1c;
  
  local_1c._1_1_ = (byte)((uint)param_1 >> 8);
  bVar2 = local_1c._1_1_;
  uVar4 = (uint)local_1c._1_1_;
  local_1c = (undefined2)param_1;
  if ((0xfc < uVar4) || (bVar1 = *(byte *)((int)param_2 + 1), bVar1 < 3)) {
    *param_2 = local_1c;
    return;
  }
  if (uVar4 < 3) {
    return;
  }
  if (bVar1 == 0xff) {
    local_28 = CONCAT22(local_28._2_2_,*param_2);
    uVar3 = FUN_00040436(param_1,local_28);
    goto LAB_00040044;
  }
  if ((bVar1 != *(byte *)((int)param_3 + 3)) || (uVar4 != *(byte *)((int)param_3 + 1))) {
    uVar6 = 0xff - ((uint)((int)(short)(0xff - (ushort)bVar2) * (int)(short)(0xff - (ushort)bVar1))
                   >> 8);
    *(char *)(param_3 + 3) = (char)uVar6;
    if (uVar6 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(char *)((int)param_3 + 7) = (char)((uVar4 * 0xff) / uVar6);
  }
  local_28 = CONCAT22(local_28._2_2_,*param_2);
  iVar5 = FUN_0003fee6(local_28,param_3[1]);
  if (iVar5 == 0) {
LAB_0004001c:
    *param_3 = local_1c;
    param_3[1] = *param_2;
    local_1c = CONCAT11(*(undefined1 *)((int)param_3 + 7),(char)param_1);
    local_28 = CONCAT22(local_28._2_2_,*param_2);
    uVar3 = FUN_00040436(local_1c,local_28);
    param_3[2] = uVar3;
    *(undefined1 *)((int)param_3 + 5) = *(undefined1 *)(param_3 + 3);
  }
  else {
    local_28 = CONCAT22(local_28._2_2_,*param_3);
    iVar5 = FUN_0003fee6(param_1,local_28);
    if (iVar5 == 0) goto LAB_0004001c;
  }
  uVar3 = param_3[2];
LAB_00040044:
  *param_2 = uVar3;
  return;
}

