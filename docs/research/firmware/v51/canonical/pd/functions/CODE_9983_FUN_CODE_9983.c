/* Address: CODE:9983; name: FUN_CODE_9983; body bytes: 23 */

void FUN_CODE_9983(undefined1 param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (DAT_INTMEM_b3 == '\x01') {
    puVar1 = &DAT_EXTMEM_072f;
  }
  else {
    if (DAT_INTMEM_b3 != '\0') {
      return;
    }
    puVar1 = &DAT_EXTMEM_072d;
  }
  *puVar1 = param_1;
  puVar1[1] = param_2;
  return;
}

