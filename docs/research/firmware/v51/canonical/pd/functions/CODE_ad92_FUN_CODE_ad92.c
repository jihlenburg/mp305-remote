/* Address: CODE:ad92; name: FUN_CODE_ad92; body bytes: 23 */

/* Inferred entry from 9 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_ad92(undefined2 param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  UNRECOVERED_JUMPTABLE = (code *)CONCAT11(uStackX_0,in_stack_000000ff);
  FUN_CODE_ada9((char)((ushort)param_1 >> 8),(char)param_1);
  FUN_CODE_ada9();
  FUN_CODE_ada9();
  FUN_CODE_ada9();
                    /* WARNING: Could not recover jumptable at 0xada8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

