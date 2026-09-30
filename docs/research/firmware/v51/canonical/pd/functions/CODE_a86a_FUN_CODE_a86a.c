/* Address: CODE:a86a; name: FUN_CODE_a86a; body bytes: 12 */

undefined1
FUN_CODE_a86a(undefined1 param_1,byte param_2,undefined1 param_3,undefined1 param_4,char param_5)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)CONCAT11(param_3,param_1);
  do {
    puVar1 = (undefined1 *)(ushort)param_2;
    param_2 = param_2 + 1;
    *puVar2 = *puVar1;
    puVar2 = puVar2 + 1;
    param_5 = param_5 + -1;
  } while (param_5 != '\0');
  return param_4;
}

