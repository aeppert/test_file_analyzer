# TEST File Analyzer
# Aaron Eppert (aaron.eppert@packetsled.com)
#

@load frameworks/files/extract-all-files.bro

export {
    global allowed: set[string] = set( "application/x-dosexec" );
}

event file_sniff(f: fa_file, meta: fa_metadata) 
{
    if( !meta?$mime_type )
        return;
    
    if ( meta$mime_type !in allowed )
        return;

    Files::add_analyzer(f, Files::ANALYZER_TEST);
}

event file_test(f: fa_file)
{    
    print fmt("file_test called for %s", f);
}