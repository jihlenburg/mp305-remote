/* Address: CODE:ad79; name: FUN_CODE_ad79; body bytes: 25 */

void FUN_CODE_ad79(undefined1 *param_1)

{
  undefined1 *puVar1;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  puVar1 = (undefined1 *)CONCAT11(uStackX_0,in_stack_000000ff);
  *param_1 = *puVar1;
  param_1['\x01'] = puVar1[1];
  param_1['\x02'] = puVar1[2];
  param_1['\x03'] = puVar1[3];
                    /* WARNING: Could not recover jumptable at 0xad91. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(puVar1 + 4))();
  return;
}

