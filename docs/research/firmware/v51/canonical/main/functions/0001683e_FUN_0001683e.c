/* Address: 0001683e; name: FUN_0001683e; body bytes: 20 */

undefined4 FUN_0001683e(uint *param_1)

{
  *param_1 = *param_1 & 0xfffffffe;
  *param_1 = *param_1 | 0x8000;
  return 0;
}

