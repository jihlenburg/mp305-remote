/* Address: 0001de7e; name: FUN_0001de7e; body bytes: 60 */

undefined4 FUN_0001de7e(int param_1,int param_2,undefined2 *param_3)

{
  undefined4 uVar1;
  
  uVar1 = 0xfffffffd;
  if (param_3 != (undefined2 *)0x0) {
    param_1 = param_1 + param_2 * 4;
    *(undefined2 *)(param_1 + 0x40) = *param_3;
    *(ushort *)(param_1 + 0x140) =
         (ushort)(byte)(*(byte *)(param_3 + 2) | *(char *)(param_3 + 3) << 2 |
                       *(char *)(param_3 + 4) << 4 | *(char *)(param_3 + 5) << 6) |
         *(ushort *)(param_1 + 0x140) & 0xff00;
    uVar1 = 0;
  }
  return uVar1;
}

