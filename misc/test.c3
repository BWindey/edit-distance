import std::io;

extern fn uint _edit_distance(char* t1, uint t1_len, char* t2, uint t2_len) @cname("edit_distance");
extern fn bool _has_max_edit_distance(char* t1, uint t1_len, char* t2, uint t2_len, uint max_distance) @cname("has_max_edit_distance");

macro uint edit_distance(String t1, String t2) {
	return _edit_distance(t1.ptr, t1.len, t2.ptr, t2.len);
}
macro bool has_max_edit_distance(String t1, String t2, uint max_distance) {
	return _has_max_edit_distance(t1.ptr, t1.len, t2.ptr, t2.len, max_distance);
}

char[64] _buffer;

fn void normal_short() @benchmark {
	File f = file::open("/usr/share/dict/words", "r")!!;
	defer (void) f.close();

	String test = "brain";
	ByteWriter buffer;
	buffer.init_with_buffer(&_buffer);
	uint x = 0;

	while (try io::readline_to_stream(&buffer, &f)) {
		if (edit_distance(test, buffer.str_view()) <= 2) {
			x++;
		}
		buffer.index = 0;
	}
}

fn void normal_long() @benchmark {
	File f = file::open("/usr/share/dict/words", "r")!!;
	defer (void) f.close();

	String test = "unsophisticated";
	ByteWriter buffer;
	buffer.init_with_buffer(&_buffer);
	uint x = 0;

	while (try io::readline_to_stream(&buffer, &f)) {
		if (edit_distance(test, buffer.str_view()) <= 4) {
			x++;
		}
		buffer.index = 0;
	}
}

fn void has_max_short() @benchmark {
	File f = file::open("/usr/share/dict/words", "r")!!;
	defer (void) f.close();

	String test = "brain";
	ByteWriter buffer;
	buffer.init_with_buffer(&_buffer);
	uint x = 0;

	while (try io::readline_to_stream(&buffer, &f)) {
		if (has_max_edit_distance(test, buffer.str_view(), 2)) {
			x++;
		}
		buffer.index = 0;
	}
}

fn void has_max_long() @benchmark {
	File f = file::open("/usr/share/dict/words", "r")!!;
	defer (void) f.close();

	String test = "unsophisticated";
	ByteWriter buffer;
	buffer.init_with_buffer(&_buffer);
	uint x = 0;

	while (try io::readline_to_stream(&buffer, &f)) {
		if (has_max_edit_distance(test, buffer.str_view(), 4)) {
			x++;
		}
		buffer.index = 0;
	}
}

fn void test_same() @test {
	File f = file::open("/usr/share/dict/words", "r")!!;
	defer (void) f.close();

	String test = "sophisticated";
	ByteWriter buffer;
	buffer.init_with_buffer(&_buffer);
	uint x = 0;

	while (try io::readline_to_stream(&buffer, &f)) {
		uint ed = edit_distance(test, buffer.str_view());
		assert(has_max_edit_distance(test, buffer.str_view(), ed));
		buffer.index = 0;
	}
}

fn void main() {
	File f = file::open("/usr/share/dict/words", "r")!!;
	defer (void) f.close();

	String test = "unsophisticated";
	ByteWriter buffer;
	buffer.init_with_buffer(&_buffer);
	uint x = 0;

	buffer.index = 0;
}
