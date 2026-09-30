/* Address: CODE:a862; name: FUN_CODE_a862; body bytes: 8 */

undefined1 FUN_CODE_a862(byte param_1,byte param_2,undefined1 param_3,char param_4)

{
  undefined1 *puVar1;
  
  do {
    puVar1 = (undefined1 *)(ushort)param_2;
    param_2 = param_2 + 1;
    *(undefined1 *)(ushort)param_1 = *puVar1;
    param_1 = param_1 + 1;
    param_4 = param_4 + -1;
  } while (param_4 != '\0');
  return param_3;
}

