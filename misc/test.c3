import std::io;

extern fn uint _edit_distance(char* t1, uint t1_len, char* t2, uint t2_len) @cname("edit_distance");

macro uint edit_distance(String t1, String t2) {
	return _edit_distance(t1.ptr, t1.len, t2.ptr, t2.len);
}

fn int main(String[] args) {
	if (args.len != 3) {
		io::eprintn("You need to pass exactly 2 arguments");
		return 1;
	}

	uint ed = edit_distance(args[1], args[2]);
	io::printfn("Edit distance: %s", ed);

	return 0;
}
