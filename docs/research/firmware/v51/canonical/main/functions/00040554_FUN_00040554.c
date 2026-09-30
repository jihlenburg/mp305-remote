/* Address: 00040554; name: FUN_00040554; body bytes: 20 */

int FUN_00040554(uint param_1)

{
  return (param_1 & 0xff) + (param_1 & 0xff00) + (param_1 & 0xff0000);
}

