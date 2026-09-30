/* Address: 0001ddd2; name: FUN_0001ddd2; body bytes: 60 */

undefined4 FUN_0001ddd2(int param_1,int param_2,uint *param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (param_3 == (uint *)0x0) {
    uVar2 = 0xfffffffd;
  }
  else {
    puVar1 = (undefined4 *)(param_1 + param_2 * 4);
    *puVar1 = 0;
    puVar1[2] = (uint)(ushort)param_3[3];
    *(uint *)(param_1 + 0x10) =
         *(uint *)(param_1 + 0x10) & ~(0x87f2 << (param_2 << 4 & 0xffU)) |
         ((*param_3 | param_3[1] | param_3[2]) & 0x87f2) << (param_2 << 4 & 0xffU);
  }
  return uVar2;
}

