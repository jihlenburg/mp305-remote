/* Address: CODE:9a23; name: FUN_CODE_9a23; body bytes: 22 */

/* Inferred entry from 13 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_9a23(byte param_1,byte param_2)

{
  byte *pbVar1;
  
  if (DAT_INTMEM_b3 == '\x01') {
    pbVar1 = &DAT_EXTMEM_0633;
  }
  else {
    pbVar1 = &DAT_EXTMEM_0631;
  }
  *pbVar1 = *pbVar1 | param_1;
  pbVar1[1] = pbVar1[1] | param_2;
  return;
}

