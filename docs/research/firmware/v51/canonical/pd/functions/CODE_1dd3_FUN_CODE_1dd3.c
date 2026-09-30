/* Address: CODE:1dd3; name: FUN_CODE_1dd3; body bytes: 8 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_1dd3(char *param_1,char param_2,byte param_3)

{
  FUN_CODE_aa37(0,2,param_2 + (*param_1 - ((CARRY1(param_1['\x01'],param_3) << 7) >> 7)),
                param_1['\x01'] + param_3);
  return;
}

