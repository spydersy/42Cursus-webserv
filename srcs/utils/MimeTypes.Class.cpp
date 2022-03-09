/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeTypes.Class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:19:04 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/10 00:01:51 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

/*
** CONSTRUCTORS & DESTRUCTORS : ************************************************
*/
MimeTypes::MimeTypes(std::string PATH) :    _path(PATH),
                                            _extension(""),
                                            _contentType("") {
    std::cout << "MimeTypes Constructor Called :) " << std::endl;
    _types.push_back(std::make_pair("3gpp", "audio/3gpp"));
    _types.push_back(std::make_pair("jpm", "video/jpm"));
    _types.push_back(std::make_pair("mp3", "audio/mp3"));
    _types.push_back(std::make_pair("rtf", "text/rtf"));
    _types.push_back(std::make_pair("apng", "image/apng"));
    _types.push_back(std::make_pair("wav", "audio/wave"));
    _types.push_back(std::make_pair("asc", "application/pgp-signature"));
    _types.push_back(std::make_pair("xml", "text/xml"));
    _types.push_back(std::make_pair("atomcat", "application/atomcat+xml"));
    _types.push_back(std::make_pair("3g2", "video/3gpp2"));
    _types.push_back(std::make_pair("au", "audio/basic"));
    _types.push_back(std::make_pair("3gp", "video/3gpp"));
    _types.push_back(std::make_pair("bdoc", "application/bdoc"));
    _types.push_back(std::make_pair("3gpp", "video/3gpp"));
    _types.push_back(std::make_pair("bmp", "image/bmp"));
    _types.push_back(std::make_pair("ac", "application/pkix-attr-cert"));
    _types.push_back(std::make_pair("buffer", "application/octet-stream"));
    _types.push_back(std::make_pair("adp", "audio/adpcm"));
    _types.push_back(std::make_pair("cdmia", "application/cdmi-capability"));
    _types.push_back(std::make_pair("ai", "application/postscript"));
    _types.push_back(std::make_pair("cdmid", "application/cdmi-domain"));
    _types.push_back(std::make_pair("appcache", "text/cache-manifest"));
    _types.push_back(std::make_pair("cdmiq", "application/cdmi-queue"));
    _types.push_back(std::make_pair("atom", "application/atom+xml"));
    _types.push_back(std::make_pair("cgm", "image/cgm"));
    _types.push_back(std::make_pair("atomsvc", "application/atomsvc+xml"));
    _types.push_back(std::make_pair("coffee", "text/coffeescript"));
    _types.push_back(std::make_pair("aw", "application/applixware"));
    _types.push_back(std::make_pair("cpt", "application/mac-compactpro"));
    _types.push_back(std::make_pair("bin", "application/octet-stream"));
    _types.push_back(std::make_pair("css", "text/css"));
    _types.push_back(std::make_pair("bpk", "application/octet-stream"));
    _types.push_back(std::make_pair("cu", "application/cu-seeme"));
    _types.push_back(std::make_pair("ccxml", "application/ccxml+xml"));
    _types.push_back(std::make_pair("dbk", "application/docbook+xml"));
    _types.push_back(std::make_pair("cdmic", "application/cdmi-container"));
    _types.push_back(std::make_pair("def", "text/plain"));
    _types.push_back(std::make_pair("cdmio", "application/cdmi-object"));
    _types.push_back(std::make_pair("disposition-notification", "message/disposition-notification"));
    _types.push_back(std::make_pair("cer", "application/pkix-cert"));
    _types.push_back(std::make_pair("distz", "application/octet-stream"));
    _types.push_back(std::make_pair("class", "application/java-vm"));
    _types.push_back(std::make_pair("dmg", "application/octet-stream"));
    _types.push_back(std::make_pair("conf", "text/plain"));
    _types.push_back(std::make_pair("doc", "application/msword"));
    _types.push_back(std::make_pair("crl", "application/pkix-crl"));
    _types.push_back(std::make_pair("drle", "image/dicom-rle"));
    _types.push_back(std::make_pair("csv", "text/csv"));
    _types.push_back(std::make_pair("dtd", "application/xml-dtd"));
    _types.push_back(std::make_pair("davmount", "application/davmount+xml"));
    _types.push_back(std::make_pair("ear", "application/java-archive"));
    _types.push_back(std::make_pair("deb", "application/octet-stream"));
    _types.push_back(std::make_pair("elc", "application/octet-stream"));
    _types.push_back(std::make_pair("deploy", "application/octet-stream"));
    _types.push_back(std::make_pair("eml", "message/rfc822"));
    _types.push_back(std::make_pair("dist", "application/octet-stream"));
    _types.push_back(std::make_pair("eps", "application/postscript"));
    _types.push_back(std::make_pair("dll", "application/octet-stream"));
    _types.push_back(std::make_pair("es", "application/ecmascript"));
    _types.push_back(std::make_pair("dms", "application/octet-stream"));
    _types.push_back(std::make_pair("exi", "application/exi"));
    _types.push_back(std::make_pair("dot", "application/msword"));
    _types.push_back(std::make_pair("ez", "application/andrew-inset"));
    _types.push_back(std::make_pair("dssc", "application/dssc+der"));
    _types.push_back(std::make_pair("g3", "image/g3fax"));
    _types.push_back(std::make_pair("dump", "application/octet-stream"));
    _types.push_back(std::make_pair("geojson", "application/geo+json"));
    _types.push_back(std::make_pair("ecma", "application/ecmascript"));
    _types.push_back(std::make_pair("glb", "model/gltf-binary"));
    _types.push_back(std::make_pair("emf", "image/emf"));
    _types.push_back(std::make_pair("gml", "application/gml+xml"));
    _types.push_back(std::make_pair("emma", "application/emma+xml"));
    _types.push_back(std::make_pair("gram", "application/srgs"));
    _types.push_back(std::make_pair("epub", "application/epub+zip"));
    _types.push_back(std::make_pair("gxf", "application/gxf"));
    _types.push_back(std::make_pair("exe", "application/octet-stream"));
    _types.push_back(std::make_pair("h261", "video/h261"));
    _types.push_back(std::make_pair("exr", "image/aces"));
    _types.push_back(std::make_pair("h264", "video/h264"));
    _types.push_back(std::make_pair("fits", "image/fits"));
    _types.push_back(std::make_pair("heics", "image/heic-sequence"));
    _types.push_back(std::make_pair("gbr", "application/rpki-ghostbusters"));
    _types.push_back(std::make_pair("heifs", "image/heif-sequence"));
    _types.push_back(std::make_pair("gif", "image/gif"));
    _types.push_back(std::make_pair("hlp", "application/winhlp"));
    _types.push_back(std::make_pair("gltf", "model/gltf+json"));
    _types.push_back(std::make_pair("htm", "text/html"));
    _types.push_back(std::make_pair("gpx", "application/gpx+xml"));
    _types.push_back(std::make_pair("ics", "text/calendar"));
    _types.push_back(std::make_pair("grxml", "application/srgs+xml"));
    _types.push_back(std::make_pair("ifb", "text/calendar"));
    _types.push_back(std::make_pair("gz", "application/gzip"));
    _types.push_back(std::make_pair("igs", "model/iges"));
    _types.push_back(std::make_pair("h263", "video/h263"));
    _types.push_back(std::make_pair("in", "text/plain"));
    _types.push_back(std::make_pair("heic", "image/heic"));
    _types.push_back(std::make_pair("ink", "application/inkml+xml"));
    _types.push_back(std::make_pair("heif", "image/heif"));
    _types.push_back(std::make_pair("ipfix", "application/ipfix"));
    _types.push_back(std::make_pair("hjson", "application/hjson"));
    _types.push_back(std::make_pair("jade", "text/jade"));
    _types.push_back(std::make_pair("hqx", "application/mac-binhex40"));
    _types.push_back(std::make_pair("jls", "image/jls"));
    _types.push_back(std::make_pair("html", "text/html"));
    _types.push_back(std::make_pair("jpe", "image/jpeg"));
    _types.push_back(std::make_pair("ief", "image/ief"));
    _types.push_back(std::make_pair("jpf", "image/jpx"));
    _types.push_back(std::make_pair("iges", "model/iges"));
    _types.push_back(std::make_pair("jpg2", "image/jp2"));
    _types.push_back(std::make_pair("img", "application/octet-stream"));
    _types.push_back(std::make_pair("jpgv", "video/jpeg"));
    _types.push_back(std::make_pair("ini", "text/plain"));
    _types.push_back(std::make_pair("jpx", "image/jpx"));
    _types.push_back(std::make_pair("inkml", "application/inkml+xml"));
    _types.push_back(std::make_pair("json", "application/json"));
    _types.push_back(std::make_pair("iso", "application/octet-stream"));
    _types.push_back(std::make_pair("jsonld", "application/ld+json"));
    _types.push_back(std::make_pair("jar", "application/java-archive"));
    _types.push_back(std::make_pair("jsx", "text/jsx"));
    _types.push_back(std::make_pair("jp2", "image/jp2"));
    _types.push_back(std::make_pair("ktx", "image/ktx"));
    _types.push_back(std::make_pair("jpeg", "image/jpeg"));
    _types.push_back(std::make_pair("list", "text/plain"));
    _types.push_back(std::make_pair("jpg", "image/jpeg"));
    _types.push_back(std::make_pair("log", "text/plain"));
    _types.push_back(std::make_pair("jpgm", "video/jpm"));
    _types.push_back(std::make_pair("lrf", "application/octet-stream"));
    _types.push_back(std::make_pair("jpm", "image/jpm"));
    _types.push_back(std::make_pair("m21", "application/mp21"));
    _types.push_back(std::make_pair("js", "application/javascript"));
    _types.push_back(std::make_pair("m2v", "video/mpeg"));
    _types.push_back(std::make_pair("json5", "application/json5"));
    _types.push_back(std::make_pair("m4a", "audio/mp4"));
    _types.push_back(std::make_pair("jsonml", "application/jsonml+json"));
    _types.push_back(std::make_pair("ma", "application/mathematica"));
    _types.push_back(std::make_pair("kar", "audio/midi"));
    _types.push_back(std::make_pair("man", "text/troff"));
    _types.push_back(std::make_pair("less", "text/less"));
    _types.push_back(std::make_pair("map", "application/json"));
    _types.push_back(std::make_pair("litcoffee", "text/coffeescript"));
    _types.push_back(std::make_pair("markdown", "text/markdown"));
    _types.push_back(std::make_pair("lostxml", "application/lost+xml"));
    _types.push_back(std::make_pair("mb", "application/mathematica"));
    _types.push_back(std::make_pair("m1v", "video/mpeg"));
    _types.push_back(std::make_pair("md", "text/markdown"));
    _types.push_back(std::make_pair("m2a", "audio/mpeg"));
    _types.push_back(std::make_pair("mesh", "model/mesh"));
    _types.push_back(std::make_pair("m3a", "audio/mpeg"));
    _types.push_back(std::make_pair("metalink", "application/metalink+xml"));
    _types.push_back(std::make_pair("m4p", "application/mp4"));
    _types.push_back(std::make_pair("mft", "application/rpki-manifest"));
    _types.push_back(std::make_pair("mads", "application/mads+xml"));
    _types.push_back(std::make_pair("midi", "audio/midi"));
    _types.push_back(std::make_pair("manifest", "text/cache-manifest"));
    _types.push_back(std::make_pair("mj2", "video/mj2"));
    _types.push_back(std::make_pair("mar", "application/octet-stream"));
    _types.push_back(std::make_pair("mjs", "application/javascript"));
    _types.push_back(std::make_pair("mathml", "application/mathml+xml"));
    _types.push_back(std::make_pair("mods", "application/mods+xml"));
    _types.push_back(std::make_pair("mbox", "application/mbox"));
    _types.push_back(std::make_pair("mp2", "audio/mpeg"));
    _types.push_back(std::make_pair("me", "text/troff"));
    _types.push_back(std::make_pair("mp2a", "audio/mpeg"));
    _types.push_back(std::make_pair("meta4", "application/metalink4+xml"));
    _types.push_back(std::make_pair("mp4", "video/mp4"));
    _types.push_back(std::make_pair("mets", "application/mets+xml"));
    _types.push_back(std::make_pair("mp4s", "application/mp4"));
    _types.push_back(std::make_pair("mid", "audio/midi"));
    _types.push_back(std::make_pair("mpd", "application/dash+xml"));
    _types.push_back(std::make_pair("mime", "message/rfc822"));
    _types.push_back(std::make_pair("mpeg", "video/mpeg"));
    _types.push_back(std::make_pair("mjp2", "video/mj2"));
    _types.push_back(std::make_pair("mpg4", "video/mp4"));
    _types.push_back(std::make_pair("mml", "text/mathml"));
    _types.push_back(std::make_pair("mrc", "application/marc"));
    _types.push_back(std::make_pair("mov", "video/quicktime"));
    _types.push_back(std::make_pair("ms", "text/troff"));
    _types.push_back(std::make_pair("mp21", "application/mp21"));
    _types.push_back(std::make_pair("msh", "model/mesh"));
    _types.push_back(std::make_pair("mp3", "audio/mpeg"));
    _types.push_back(std::make_pair("msm", "application/octet-stream"));
    _types.push_back(std::make_pair("mp4a", "audio/mp4"));
    _types.push_back(std::make_pair("mxf", "application/mxf"));
    _types.push_back(std::make_pair("mp4v", "video/mp4"));
    _types.push_back(std::make_pair("n3", "text/n3"));
    _types.push_back(std::make_pair("mpe", "video/mpeg"));
    _types.push_back(std::make_pair("oda", "application/oda"));
    _types.push_back(std::make_pair("mpg", "video/mpeg"));
    _types.push_back(std::make_pair("ogg", "audio/ogg"));
    _types.push_back(std::make_pair("mpga", "audio/mpeg"));
    _types.push_back(std::make_pair("ogx", "application/ogg"));
    _types.push_back(std::make_pair("mrcx", "application/marcxml+xml"));
    _types.push_back(std::make_pair("onepkg", "application/onenote"));
    _types.push_back(std::make_pair("mscml", "application/mediaservercontrol+xml"));
    _types.push_back(std::make_pair("onetoc", "application/onenote"));
    _types.push_back(std::make_pair("msi", "application/octet-stream"));
    _types.push_back(std::make_pair("opf", "application/oebps-package+xml"));
    _types.push_back(std::make_pair("msp", "application/octet-stream"));
    _types.push_back(std::make_pair("owl", "application/rdf+xml"));
    _types.push_back(std::make_pair("mxml", "application/xv+xml"));
    _types.push_back(std::make_pair("p10", "application/pkcs10"));
    _types.push_back(std::make_pair("nb", "application/mathematica"));
    _types.push_back(std::make_pair("p7m", "application/pkcs7-mime"));
    _types.push_back(std::make_pair("oga", "audio/ogg"));
    _types.push_back(std::make_pair("p8", "application/pkcs8"));
    _types.push_back(std::make_pair("ogv", "video/ogg"));
    _types.push_back(std::make_pair("pfr", "application/font-tdpfr"));
    _types.push_back(std::make_pair("omdoc", "application/omdoc+xml"));
    _types.push_back(std::make_pair("pkg", "application/octet-stream"));
    _types.push_back(std::make_pair("onetmp", "application/onenote"));
    _types.push_back(std::make_pair("pkipath", "application/pkix-pkipath"));
    _types.push_back(std::make_pair("onetoc2", "application/onenote"));
    _types.push_back(std::make_pair("png", "image/png"));
    _types.push_back(std::make_pair("otf", "font/otf"));
    _types.push_back(std::make_pair("ps", "application/postscript"));
    _types.push_back(std::make_pair("oxps", "application/oxps"));
    _types.push_back(std::make_pair("qt", "video/quicktime"));
    _types.push_back(std::make_pair("p7c", "application/pkcs7-mime"));
    _types.push_back(std::make_pair("rdf", "application/rdf+xml"));
    _types.push_back(std::make_pair("p7s", "application/pkcs7-signature"));
    _types.push_back(std::make_pair("rl", "application/resource-lists+xml"));
    _types.push_back(std::make_pair("pdf", "application/pdf"));
    _types.push_back(std::make_pair("rmi", "audio/midi"));
    _types.push_back(std::make_pair("pgp", "application/pgp-encrypted"));
    _types.push_back(std::make_pair("rng", "application/xml"));
    _types.push_back(std::make_pair("pki", "application/pkixcmp"));
    _types.push_back(std::make_pair("roff", "text/troff"));
    _types.push_back(std::make_pair("pls", "application/pls+xml"));
    _types.push_back(std::make_pair("rs", "application/rls-services+xml"));
    _types.push_back(std::make_pair("prf", "application/pics-rules"));
    _types.push_back(std::make_pair("rss", "application/rss+xml"));
    _types.push_back(std::make_pair("pskcxml", "application/pskc+xml"));
    _types.push_back(std::make_pair("rtx", "text/richtext"));
    _types.push_back(std::make_pair("raml", "application/raml+yaml"));
    _types.push_back(std::make_pair("sbml", "application/sbml+xml"));
    _types.push_back(std::make_pair("rif", "application/reginfo+xml"));
    _types.push_back(std::make_pair("scs", "application/scvp-cv-response"));
    _types.push_back(std::make_pair("rld", "application/resource-lists-diff+xml"));
    _types.push_back(std::make_pair("ser", "application/java-serialized-object"));
    _types.push_back(std::make_pair("rnc", "application/relax-ng-compact-syntax"));
    _types.push_back(std::make_pair("setreg", "application/set-registration-initiation"));
    _types.push_back(std::make_pair("roa", "application/rpki-roa"));
    _types.push_back(std::make_pair("sgm", "text/sgml"));
    _types.push_back(std::make_pair("rq", "application/sparql-query"));
    _types.push_back(std::make_pair("shex", "text/shex"));
    _types.push_back(std::make_pair("rsd", "application/rsd+xml"));
    _types.push_back(std::make_pair("shtml", "text/html"));
    _types.push_back(std::make_pair("rtf", "application/rtf"));
    _types.push_back(std::make_pair("sil", "audio/silk"));
    _types.push_back(std::make_pair("s3m", "audio/s3m"));
    _types.push_back(std::make_pair("slim", "text/slim"));
    _types.push_back(std::make_pair("scq", "application/scvp-cv-request"));
    _types.push_back(std::make_pair("smi", "application/smil+xml"));
    _types.push_back(std::make_pair("sdp", "application/sdp"));
    _types.push_back(std::make_pair("snd", "audio/basic"));
    _types.push_back(std::make_pair("setpay", "application/set-payment-initiation"));
    _types.push_back(std::make_pair("spp", "application/scvp-vp-response"));
    _types.push_back(std::make_pair("sgi", "image/sgi"));
    _types.push_back(std::make_pair("spx", "audio/ogg"));
    _types.push_back(std::make_pair("sgml", "text/sgml"));
    _types.push_back(std::make_pair("srx", "application/sparql-results+xml"));
    _types.push_back(std::make_pair("shf", "application/shf+xml"));
    _types.push_back(std::make_pair("ssml", "application/ssml+xml"));
    _types.push_back(std::make_pair("sig", "application/pgp-signature"));
    _types.push_back(std::make_pair("styl", "text/stylus"));
    _types.push_back(std::make_pair("silo", "model/mesh"));
    _types.push_back(std::make_pair("svg", "image/svg+xml"));
    _types.push_back(std::make_pair("slm", "text/slim"));
    _types.push_back(std::make_pair("t", "text/troff"));
    _types.push_back(std::make_pair("smil", "application/smil+xml"));
    _types.push_back(std::make_pair("tei", "application/tei+xml"));
    _types.push_back(std::make_pair("so", "application/octet-stream"));
    _types.push_back(std::make_pair("text", "text/plain"));
    _types.push_back(std::make_pair("spq", "application/scvp-vp-request"));
    _types.push_back(std::make_pair("tfx", "image/tiff-fx"));
    _types.push_back(std::make_pair("sru", "application/sru+xml"));
    _types.push_back(std::make_pair("tiff", "image/tiff"));
    _types.push_back(std::make_pair("ssdl", "application/ssdl+xml"));
    _types.push_back(std::make_pair("ts", "video/mp2t"));
    _types.push_back(std::make_pair("stk", "application/hyperstudio"));
    _types.push_back(std::make_pair("tsv", "text/tab-separated-values"));
    _types.push_back(std::make_pair("stylus", "text/stylus"));
    _types.push_back(std::make_pair("ttf", "font/ttf"));
    _types.push_back(std::make_pair("svgz", "image/svg+xml"));
    _types.push_back(std::make_pair("txt", "text/plain"));
    _types.push_back(std::make_pair("t38", "image/t38"));
    _types.push_back(std::make_pair("u8hdr", "message/global-headers"));
    _types.push_back(std::make_pair("teicorpus", "application/tei+xml"));
    _types.push_back(std::make_pair("u8msg", "message/global"));
    _types.push_back(std::make_pair("tfi", "application/thraud+xml"));
    _types.push_back(std::make_pair("uris", "text/uri-list"));
    _types.push_back(std::make_pair("tif", "image/tiff"));
    _types.push_back(std::make_pair("vcard", "text/vcard"));
    _types.push_back(std::make_pair("tr", "text/troff"));
    _types.push_back(std::make_pair("vtt", "text/vtt"));
    _types.push_back(std::make_pair("tsd", "application/timestamped-data"));
    _types.push_back(std::make_pair("war", "application/java-archive"));
    _types.push_back(std::make_pair("ttc", "font/collection"));
    _types.push_back(std::make_pair("wav", "audio/wav"));
    _types.push_back(std::make_pair("ttl", "text/turtle"));
    _types.push_back(std::make_pair("webm", "video/webm"));
    _types.push_back(std::make_pair("u8dsn", "message/global-delivery-status"));
    _types.push_back(std::make_pair("webp", "image/webp"));
    _types.push_back(std::make_pair("u8mdn", "message/global-disposition-notification"));
    _types.push_back(std::make_pair("wmf", "image/wmf"));
    _types.push_back(std::make_pair("uri", "text/uri-list"));
    _types.push_back(std::make_pair("woff2", "font/woff2"));
    _types.push_back(std::make_pair("urls", "text/uri-list"));
    _types.push_back(std::make_pair("wsdl", "application/wsdl+xml"));
    _types.push_back(std::make_pair("vrml", "model/vrml"));
    _types.push_back(std::make_pair("x3d", "model/x3d+xml"));
    _types.push_back(std::make_pair("vxml", "application/voicexml+xml"));
    _types.push_back(std::make_pair("x3dbz", "model/x3d+binary"));
    _types.push_back(std::make_pair("wasm", "application/wasm"));
    _types.push_back(std::make_pair("x3dvz", "model/x3d+vrml"));
    _types.push_back(std::make_pair("weba", "audio/webm"));
    _types.push_back(std::make_pair("xaml", "application/xaml+xml"));
    _types.push_back(std::make_pair("webmanifest", "application/manifest+json"));
    _types.push_back(std::make_pair("xdssc", "application/dssc+xml"));
    _types.push_back(std::make_pair("wgt", "application/widget"));
    _types.push_back(std::make_pair("xer", "application/patch-ops-error+xml"));
    _types.push_back(std::make_pair("woff", "font/woff"));
    _types.push_back(std::make_pair("xhtml", "application/xhtml+xml"));
    _types.push_back(std::make_pair("wrl", "model/vrml"));
    _types.push_back(std::make_pair("xm", "audio/xm"));
    _types.push_back(std::make_pair("wspolicy", "application/wspolicy+xml"));
    _types.push_back(std::make_pair("xop", "application/xop+xml"));
    _types.push_back(std::make_pair("x3db", "model/x3d+binary"));
    _types.push_back(std::make_pair("xsd", "application/xml"));
    _types.push_back(std::make_pair("x3dv", "model/x3d+vrml"));
    _types.push_back(std::make_pair("xslt", "application/xslt+xml"));
    _types.push_back(std::make_pair("x3dz", "model/x3d+xml"));
    _types.push_back(std::make_pair("xvm", "application/xv+xml"));
    _types.push_back(std::make_pair("xdf", "application/xcap-diff+xml"));
    _types.push_back(std::make_pair("yaml", "text/yaml"));
    _types.push_back(std::make_pair("xenc", "application/xenc+xml"));
    _types.push_back(std::make_pair("yin", "application/yin+xml"));
    _types.push_back(std::make_pair("xht", "application/xhtml+xml"));
    _types.push_back(std::make_pair("zip", "application/zip"));
    _types.push_back(std::make_pair("xhvml", "application/xv+xml"));
    _types.push_back(std::make_pair("xml", "application/xml"));
    _types.push_back(std::make_pair("xpl", "application/xproc+xml"));
    _types.push_back(std::make_pair("xsl", "application/xml"));
    _types.push_back(std::make_pair("xspf", "application/xspf+xml"));
    _types.push_back(std::make_pair("xvml", "application/xv+xml"));
    _types.push_back(std::make_pair("yang", "application/yang"));
    _types.push_back(std::make_pair("yml", "text/yaml"));
    _mimetype.first = "def";
    _mimetype.second = "text/plain";
}
MimeTypes::~MimeTypes() {
            std::cout << "MimeTypes Destructor Called :'( " << std::endl;
}

/*
** GETTERS : *******************************************************************
*/
std::string                         MimeTypes::getExtension() { return this->_extension; }
std::pair<std::string, std::string> MimeTypes::get_mimetype() {
    badExtension();
    return this->_mimetype;
}

/*
** SETTERS : *******************************************************************
*/
void                                MimeTypes::set_path(std::string path) { this->_path = path; }

/*
** METHODS : *******************************************************************
*/
size_t    MimeTypes::haveExtension() {
    size_t      index;
    std::cout << "DBG_MimeTypes::haveExtension :: [" << _path << "]" << std::endl;
    if ((index = _path.find_last_of(".")) != NPOS) {
        std::cout << "EX INDEX : " << index << std::endl;
        return index;
    }
    std::cout << "EX INDEX : NPOS" << std::endl;
    return NPOS;
}

bool    MimeTypes::badExtension() {
    // std::string path = _REQUEST.getPath();
    size_t      index = this->haveExtension();

    if (index == NPOS) {
        std::cout << "BAAAAAAD1" << std::endl;
        return true;
    }
    _extension = _path.substr(index + 1);
    for (std::vector<std::pair<std::string, std::string> >::iterator it = _types.begin(); it < _types.end(); it++) {
        if (_extension.compare(it->first) == 0) {
            _mimetype = *it;
            std::cout << "NOT BAAAAAAD : " << it->first << " | " << it->second << std::endl;
            return false;
        }
    }
    std::cout << "BAAAAAAD2" << std::endl;
    return true;
}