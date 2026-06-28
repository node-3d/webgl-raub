// oxlint-disable max-classes-per-file

export type TActiveInfo = Readonly<{
	size: number;
	type: number;
	name: string;
}>;

export type TResourceId = number;

export class WebGLObject<TResource = TResourceId> {
	public _: TResource;
	
	public constructor(_: TResource) {
		this._ = _;
	}
}

export class WebGLActiveInfo {
	public _: TActiveInfo;
	
	public size: number;
	
	public type: number;
	
	public name: string;
	
	public constructor(_: TActiveInfo) {
		this._ = _;
		this.size = _.size;
		this.type = _.type;
		this.name = _.name;
	}
}

export class WebGLRenderingContext extends WebGLObject {}
export class WebGLProgram extends WebGLObject {
	declare public readonly webglResourceType: 'WebGLProgram';
}
export class WebGLQuery extends WebGLObject {
	declare public readonly webglResourceType: 'WebGLQuery';
}
export class WebGLShader extends WebGLObject {
	declare public readonly webglResourceType: 'WebGLShader';
}
export class WebGLVertexArrayObject extends WebGLObject {
	declare public readonly webglResourceType: 'WebGLVertexArrayObject';
}
export class WebGLBuffer extends WebGLObject {
	declare public readonly webglResourceType: 'WebGLBuffer';
}
export class WebGLFramebuffer extends WebGLObject {
	declare public readonly webglResourceType: 'WebGLFramebuffer';
}
export class WebGLRenderbuffer extends WebGLObject {
	declare public readonly webglResourceType: 'WebGLRenderbuffer';
}
export class WebGLTexture extends WebGLObject {
	declare public readonly webglResourceType: 'WebGLTexture';
}
export class WebGLUniformLocation extends WebGLObject {
	declare public readonly webglResourceType: 'WebGLUniformLocation';
}
export class WebGLTransformFeedback extends WebGLObject {
	declare public readonly webglResourceType: 'WebGLTransformFeedback';
}
export class WebGLSampler extends WebGLObject {
	declare public readonly webglResourceType: 'WebGLSampler';
}
export class WebGLSync extends WebGLObject<object> {
	declare public readonly webglResourceType: 'WebGLSync';
}
export class WebGL2RenderingContext extends WebGLObject {}
