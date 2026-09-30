/* Address: 0001fff0; name: append_stuffed_byte; body bytes: 14 */

undefined1 * append_stuffed_byte(undefined4 param_1,int param_2,undefined1 *param_3)

{
  undefined1 *puVar1;
  
  *param_3 = (char)param_2;
  puVar1 = param_3 + 1;
  if (param_2 == 0xaa) {
    puVar1 = param_3 + 2;
    param_3[1] = 0xaa;
  }
  return puVar1;
}

