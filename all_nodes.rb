class A::B < ::C
    alias foo bar
    undef foo

    def m(a, (foo), b = foo, *c, d:, e: foo, **f, &g)
        __FILE__
        __LINE__
        __ENCODING__

        true
        false
        nil

        -1
        -1.0
        -1r
        -1i

        a = 1
        a
        @foo
        @foo = 1
        @@foo
        @@foo = 1
        $foo
        $foo = 1
        $1
        $`

        a &&= b
        a & b
        a and b
        a ||= b
        a || b
        a or b

        case foo
        in [1, [2], 3,] then true
        in Foo
            true
        in Foo[1, 2, 3]
            true
        in { foo: bar }
            true
        in ^foo
            true
        in foo => bar then true
        in [*, foo, *] then
            nil
        in foo if bar
            nil
        in foo unless bar
            nil
        in foo | bar then
            nil
        in **nil then
            nil
        in *foo then
            nil
        else
            nil
        end

        case foo
        in bar
            nil
        else
            # empty else
        end

        :foo
        :"foo #{bar}"
        "foo"
        "foo #{bar}"
        `foo`

        <<-HERE
        HERE

        <<-`HERE`
        HERE

        for a in [1, 2, 3] do
            "test"
        end

        proc { |;foo| foo }
        proc { |procarg| body }
        proc { |(procarg)| body }

        foo.bar(1, *baz, **baz, &baz)
        foo.bar = 42
        foo&.bar()
        foo&.bar = 42

        (foo..bar)
        (foo..)
        (..bar)
        (foo...bar)
        (foo...)
        (...bar)

        foo do
            break 42
            return 42
            yield(42)
            next 42
            redo
            retry
            super(foo)
            super
        end

        case foo
        when bar then nil
        else
            nil
        end

        defined?(foo)

        if foo..bar; end
        if foo...bar; end

        begin
            foo
        rescue E => e
            bar
        else
            baz
        ensure
            foo
        end

        { 'foo': bar, :baz => foo }

        if foo then bar else baz; end
        foo if bar
        foo unless bar
        foo ? bar : baz

        foo in bar

        foo[1, 2]
        foo[1, 2] = 3

        begin
        end

        ->() {}

        (a, b) = [c, d]

        if /foo/
        end

        /(?<match>bar)/ =~ 'bar'

        foo { _1 }

        foo += bar

        /foo/mix

        until foo do
            bar
        end

        begin
            foo
        end until bar

        while foo do
            bar
        end

        begin
            foo
        end while bar
    end

    def self.foo
    end

    def m() = 42
    def self.m() = 42

    module M
        class << self
            foo
        end
    end

    ::A = 1
    ::A::B = 1
    A = 1

    def foo(...)
        bar(...)
    end

    def foo(**nil)
    end
end

BEGIN { foo }
END { foo }
