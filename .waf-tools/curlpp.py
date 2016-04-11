#! /usr/bin/env python
# encoding: utf-8

from waflib import Options
from waflib.Configure import conf

def options(opt):
    opt.add_option('--with-curlpp', type='string', default=None,
                   dest='with_curlpp', help='''Path to cURLpp, e.g., /usr/local''')

@conf
def check_curlpp(self, *k, **kw):
    root = k and k[0] or kw.get('path', None) or Options.options.with_curlpp
    mandatory = kw.get('mandatory', True)
    var = kw.get('uselib_store', 'CURLPP')

    if root:
        self.check_cxx(lib='curlpp',
                       msg='Checking for cURLpp library',
                       define_name='HAVE_%s' % var,
                       uselib_store=var,
                       mandatory=mandatory,
                       cxxflags="-I%s/include" % root,
                       linkflags="-L%s/lib" % root)
    else:
        try:
            self.check_cfg(package='curlpp',
                           args=['--cflags', '--libs'],
                           uselib_store='CURLPP',
                           mandatory=True)
        except:
            self.check_cxx(lib='curlpp',
                           msg='Checking for CURLPP library',
                           define_name='HAVE_%s' % var,
                           uselib_store=var,
                           mandatory=mandatory)
